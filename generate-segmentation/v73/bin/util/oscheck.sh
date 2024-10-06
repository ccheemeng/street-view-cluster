#!/bin/sh
#set -x
#
# usage:        oscheck.sh
#
# abstract:     This Bourne Shell script determines the OS level of the
#               system and responds according to what it finds. There
#               are four numbers of interest:
#
#                   minimum_ver - minimum version allowed to run
#                   release_ver - release version
#                   future_ver  - future version that we know doesn't work
#
#                                 Note: "-" means infinite and is allowed
#                                       only for future_ver
#
#                   version     - current version
#
#		and the environment variable:
#
#		    OSCHECK_ENFORCE_LIMITS - used to determine whether to
#					     ignore the limits when
#					     deciding how to respond.
#
#					  !=  0  (enforce limits: DEFAULT)
#					   =  0  (ignore limits)
#
#               We check for:
#
#                   minimum_ver<=release_ver<=future_ver
#
#               If this condition is not met on the current platform
#               no further analysis is done and the behavior depends
#               on the value of oscheck_debug set in this script.
#               If oscheck_debug=1 an internal error message is
#               generated and you are asked to quit. If oscheck_debug=0
#               then a normal return is done with no messages produced
#               and an attempt is made to start MATLAB.
#
#               Here are the cases tested and the resulting behavior:
#
#               If version > future_ver ||
#                  version == future_ver && release_ver < future_ver
#		     if OSCHECK_ENFORCE_LIMITS != 0
#                        too new warning message
#                        request to stop
#		     else
#                        no message
#                        continue
#               If release_ver <= version <= future_ver
#                    no message
#                    continue
#               If minimum_ver <= version <= release_ver 
#                    standard warning message
#                    continue
#               If version < minimum_ver
#		     if OSCHECK_ENFORCE_LIMITS != 0
#                        too old warning message
#                        request to stop
#		     else
#                        standard warning message
#                        continue
#
#               Arch      - Machine architecture variable must be set
#
# note(s):      1. This routine must be called using a . (period)
#
#               2. token is the version in N.N... form
#
#                  sol2:    uname -r          -> token
#		   hpux:    uname -r          -> token(1)(3:end)
#                  glnx86:  /lib/libc.so.6    -> messy parsing to yield token 
#                  glnxi86: (fixed until more experience)
#		   glnxa86: /lib/libc.so.6    -> messy parsing to yield token
#		   mac:     uname -r	      -> token(1)
#
#               3. This requires at least the System V Bourne Shell since
#                  internal functions are used.
#
#               4. Algorithm:
#
#		   a. Generate version results.
#                  b. If no results then nothing to do.
#		   c. Otherwise fix error state depending on results
#		      and OSCHECK_ENFORCE_LIMITS.
#		   d. Output any messages.
#		   e. Handle input user interaction when
#		      action required to continue.
#
#               5. Assume that this routine is called using the
#                  unused temporary file defined by
#
#                     $temp_file
#
#               6. The calling routine will exit if the variable,
#                  oscheck_status, is set as follows:            
#
#                      oscheck_status=1
#
#               7. Also, any cleanup associated with of an interrupt
#                  will be handled by the calling routine.
#
#               8. Set oscheck_debug=1 to check for the consistency 
#                  of the data. Set oscheck_debug=0 for shipping.
#
# Copyright 1996-2004 The MathWorks, Inc.
# $Revision: 1.20.4.5 $  $Date: 2004/08/13 23:14:29 $
#----------------------------------------------------------------------------
#
    oscheck_status=0
#
#                   arch   OSprefix minimum_ver release_ver future_ver
#
    oslist="        sol2    SunOS    5.8         5.8         -"
    oslist="$oslist hpux    HP-UX    11.00       11.00       -"
    oslist="$oslist glnx86  glibc    2.2.0       2.2.5       -"
    oslist="$oslist glnxi64 glibc    2.2.4       2.2.4       -"
    oslist="$oslist glnxa64 glibc    2.3.2       2.3.2       -"
    oslist="$oslist mac     Darwin   7.2.0       7.2.0       -"
#
    if [ -f /bin/uname ]; then
        case $Arch in
            glnx86)
#
# Note: R13 used 'uname -r'. If you use ver below, we shipped with 2.1.2
#
# This may be run on either glnx86 or glnxa64. Note that things are OK
# since release_ver on glnx86 <= glnxa64.
#
# Example: first line from executing /lib/libc.so.6
# glnx86:  GNU C Library stable release version 2.2.5, by Roland McGrath et al.
# glnxa64: GNU C Library stable release version 2.3.2 (20030827), by Roland McGrath et al.
#
                ver=`/lib/libc.so.6 | head -n 1 | sed -e "s/^[^0-9]*//" -e "s/[ ,].*$//"`
                ;;
            glnxi64)
#
# We do not have a lot of experience yet on how things will look across multiple
# vendors. So we will pick a fixed version for now.
#
# 1. Red Hat version: ver=`/lib/libc.so.6.1 | head -n 1 | sed -e "s/^[^0-9]*//" -e "s/,.*$//"`
#
                ver=2.2.4
                ;;
            glnxa64)
#
# Example: first line from executing /lib64/libc.so.6
# glnxa64: GNU C Library stable release version 2.3.2 (20030827), by Roland McGrath et al.
#
                ver=`/lib64/libc.so.6 | head -n 1 | sed -e "s/^[^0-9]*//" -e "s/[ ,].*$//"`
                ;;
            sol2)
                ver=`/bin/uname -r`
                ;;
            hpux)  # Remove the leading capital letter and period
                ver=`/bin/uname -r | awk '{print substr($1,3)}'`
                ;;
	    Darwin)					# Mac OS X
        	ver=`/usr/bin/uname -r | awk '{print $1}'`
                ;;
            *)
		ver=`/bin/uname -r | awk '{print $1}'`
                ;;
        esac
    elif [ -f /usr/bin/uname ]; then
        case "`/usr/bin/uname`" in
	    Darwin)					# Mac OS X
                ver=`/usr/bin/uname -r | awk '{print $1}'`
                ;;
        esac
    fi
#
# Be sure that OSCHECK_ENFORCE_LIMITS has a value
#
    if [ "$OSCHECK_ENFORCE_LIMITS" = "" -o "$OSCHECK_ENFORCE_LIMITS" != "0" ]; then
	OSCHECK_ENFORCE_LIMITS=1
    fi
#
#  Set oscheck_debug=0 for shipping
#
    oscheck_debug=0
#
    results=`echo $Arch $ver "$oslist"| awk '
#---------------------------------------------------------------------------
        BEGIN { str = "0123456789"; strp = str "."
                astr = "ABCDEFGHIJKLMNOPQRSTUVWXYZ" }
        { arch = $1;
          origver = $2;
#
# remove any non-numeric prefix from the version like V, etc.
#
          ver = ""
          for (j = 1; j <= length(origver); j = j + 1)
              if (index(strp,substr(origver,j,1)) != 0) {
                  ver = substr(origver,i)
                  break
              }
          lver = length(ver)
          for (i = 3; i <= NF; i = i + 5) {
              n[$i] = $(i+1) ""
              m[$i] = $(i+2) ""
              r[$i] = $(i+3) ""
              f[$i] = $(i+4) ""
          }
          mver = m[arch]
          rver = r[arch]
          if (rver == "") exit 
          fver = f[arch]  
#
# split the minimum version
#
          nmver = split(mver,mv,".")
          for (i = 1; i <= nmver; i = i + 1)
              if (mv[i] == "") mv[i] = 0
#
# split the release version
#
          nrver = split(rver,rv,".")
          for (i = 1; i <= nrver; i = i + 1)
              if (rv[i] == "") rv[i] = 0
#
# split the future version if there is one
#
          if (fver != "-") {
              nfver = split(fver,fv,".")
              for (i = 1; i <= nfver; i = i + 1)
                  if (fv[i] == "") fv[i] = 0
          }
#
# split the actual version
# remove everything in a word after a nondigit
#
          nver = split(ver,v,".")
          for (i = 1; i <= nver; i = i + 1) {
              new = ""
              for (j = 1; j <= length(v[i]); j = j + 1)
                  if (index(str,substr(v[i],j,1)) != 0)
                      new = new substr(v[i],j,1)
                  else
                      break
              v[i] = new
              if (v[i] == "") v[i] = 0
          }
#
# errmode: 0 - no warning
#          1 - too old warning
#          2 - warning
#          3 - too new warning
#          4 - internal error (not shipped)
#
          errmode = 0
#
# check: minimum_ver<=release_ver<=future_ver
#        minimum_ver != "-"
#        release_ver != "-"
#
          if (nmver < nrver)
              ncd = nmver
          else 
              ncd = nrver
          for (i = 1; i <= ncd; i = i + 1)
              if (mv[i] + 0 > rv[i] + 0) {
                   errmode = 4
                   break
              }
              else if (mv[i] + 0 < rv[i] + 0)
                   break
          if (errmode == 0 && i == ncd + 1 && nmver > nrver)
              for (i = ncd + 1; i <= nmver; i = i + 1)
                  if (mv[i] + 0 != 0 ) {
                      errmode = 4
                      break
                  }
          if (errmode == 0 && fver != "-") {
              if (nrver < nfver)
                  ncd = nmver
              else 
                  ncd = nfver
              for (i = 1; i <= ncd; i = i + 1)
                  if (rv[i] + 0 > fv[i] + 0) {
                      errmode = 4
                      break
                  }
                  else if (rv[i] + 0 < fv[i] + 0)
                      break
              if (errmode == 0 && i == ncd + 1 && nrver > nfver)
                  for (i = ncd + 1; i <= nrver; i = i + 1)
                      if (rv[i] + 0 != 0 ) {
                          errmode = 4
                          break
                      }
          }
          if (errmode == 0 && nmver == 1 && mver == "-")
              errmode = 4
          else if (errmode == 0 && nrver == 1 && rver == "-")
              errmode = 4
#
# check whether release_ver < future_ver (futuremode = 1)
#
          if (errmode == 0) {
              futuremode = 1
              if (fver != "-") {
                  if (nrver < nfver)
                      ncd = nrver
                  else
                      ncd = nfver
                  futuremode = 0
                  for (i = 1; i <= ncd; i = i + 1)
                      if (rv[i] + 0 < fv[i] + 0) {
                          futuremode = 1
                          break
                      }
                 if (futuremode == 0)
                     for (i = ncd + 1; i <= nfver; i = i + 1)
                         if (fv[i] + 0 != 0) {
                             futuremode = 1
                             break
                         }
              }
          }
#
# check if version > future_ver ||
#          version == future_ver && release_ver < future_ver
#
          if (errmode == 0 && fver != "-") {
              if (nfver < nver)
                  ncd = nfver
              else
                  ncd = nver
              for (i = 1; i <= ncd; i = i + 1)
                  if (v[i] + 0 > fv[i] + 0) {
                      errmode = 3
                      break
                  }
                  else if (v[i] + 0 < fv[i] + 0)
                      break
              if (errmode == 0 && i == ncd + 1 && ncd == nver) {
                  for (i = ncd + 1; i <= nfver; i = i + 1)
                      if (fv[i] + 0 != 0)
                          break
                  if (i == nfver + 1 && futuremode == 1)
                      errmode = 3
                  else if (i == nfver + 1 && futuremode == 0)
#
# case: version == future_ver && release_ver == future_ver
#
                      exit
              }
              else if (errmode == 0 && i == ncd + 1 && ncd == nfver) {
                  for (i = ncd + 1; i <= nver; i = i + 1)
                      if (v[i] + 0 != 0) {
                          errmode = 3
                          break
                      }
                  if (i == nver + 1 && futuremode == 1)
                      errmode = 3
                  else if (i == nver + 1 && futuremode == 0)
#
# case: version == future_ver && release_ver == future_ver
#
                      exit
              }
          }
#
# check if release_ver <= version
#
          if (errmode == 0) {
              if (nrver < nver)
                  ncd = nrver
              else
                  ncd = nver
              for (i = 1; i <= ncd; i = i + 1)
                  if (rv[i] + 0 > v[i] + 0)
                      break
                  else if (rv[i] + 0 < v[i] + 0)
                      exit
              if (i == ncd + 1 && ncd == nrver)
                  exit
              else if (i == ncd + 1 && ncd == nver) {
                  for (i = ncd + 1; i <= nrver; i = i + 1)
                      if (rv[i] + 0 != 0)
                          break
                  if (i == nrver + 1)
                      exit
              }
          }   
#
# check if minimum_ver <= version || version < minimum_ver
#
          if (errmode == 0) {
              if (nmver < nver)
                  ncd = nmver
              else
                  ncd = nver
              for (i = 1; i <= ncd; i = i + 1)
                  if (mv[i] + 0 > v[i] + 0) {
                      errmode = 1
                      break
                  }
                  else if (mv[i] + 0 < v[i] + 0) {
                      errmode = 2
                      break
                  }
              if (i == ncd + 1 && ncd == nmver) {
                  errmode = 2
              }
              else if (i == ncd + 1 && ncd == nver) {
                  for (i = ncd + 1; i <= nmver; i = i + 1)
                      if (mv[i] + 0 != 0) {
                          errmode = 1
                          break
                      }
                  if (i == nmver + 1) 
                      errmode = 2
              }
          }   
	  print errmode, n[arch], ver, mver, rver, fver
        }'`
#---------------------------------------------------------------------------
#
# No results means no error.
#
    if [ "$results" != "" ]; then
        errmode=`echo $results | awk '{ print $1}'`
        errflag=$errmode
#
# Fix errflag depending on the value of $OSCHECK_ENFORCE_LIMITS
#
        if [ "$errmode" = "1" -a "$OSCHECK_ENFORCE_LIMITS" = "0" ]; then
	    errflag=2
        elif [ "$errmode" = "3" -a "$OSCHECK_ENFORCE_LIMITS" = "0" ]; then
	    errflag=0
        fi
#
        echo $errflag $results $oscheck_debug | awk '
#---------------------------------------------------------------------------
	{ errmode = $1
	  arch = $3
	  ver = $4
	  mver = $5
	  rver = $6
	  fver = $7
	  debug = $8
          if (errmode == 1) {
print " "   
print "----------------------------------------------------------------------------"
printf "Warning: %s %-10s - Unsupported version\n", arch, ver
printf "         %s %-10s - MATLAB built using this version\n", arch, rver
print "----------------------------------------------------------------------------"
          }
          else if (errmode == 2) {
print " "   
print "----------------------------------------------------------------------------"
printf "Warning: %s %-10s - Your version\n", arch, ver
printf "         %s %-10s - MATLAB built using this version\n", arch, rver
print "----------------------------------------------------------------------------"
          }
          else if (errmode == 3) {
print " "   
print "----------------------------------------------------------------------------"
printf "Warning: %s %-10s - Unqualified version\n", arch, ver
printf "         %s %-10s - MATLAB built using this version\n", arch, rver
print "----------------------------------------------------------------------------"
          }
          else if (errmode == 4) {
              if (debug == 0) exit
print " "   
print "----------------------------------------------------------------------------"
printf "Error: %s %-10s - Internal Error - oscheck.sh has inconsistent data\n", arch, ver
printf "       %s %-10s - Minimum supported version\n", arch, mver
printf "       %s %-10s - MATLAB built using this version\n", arch, rver
printf "       %s %-10s - Maximum supported version\n", arch, fver
print "----------------------------------------------------------------------------"
print " "
          }
        }' > $temp_file
#---------------------------------------------------------------------------
#=======================================================================
# Functions:
#=======================================================================
    echon ()    { # echo without a newline - UNIX dependent
                  #
                  # usage: echon
                  #
        if [ "`echo -n`" != "" ]; then
            echo "$1\c"
        else
            echo -n "$1"
        fi
    }
#=======================================================================
        if [ -s $temp_file ]; then
            cat $temp_file
            errtype=`cat $temp_file | awk 'NR == 3 {print $5}'`
            case "$errtype" in
                'Unsupported')
#---------------------------------------------------------------------------
echo '-> Your configuration APPEARS to be too OLD to run this MATLAB program!'
echo '----------------------------------------------------------------------------'
#---------------------------------------------------------------------------
                    ;;
                'Unqualified')
#---------------------------------------------------------------------------
echo '-> Your configuration APPEARS to be too NEW to run this MATLAB program!'
echo '----------------------------------------------------------------------------'
#---------------------------------------------------------------------------
                    ;;
                'Your')
		    if [ "$errmode" = "1" ]; then
#---------------------------------------------------------------------------
echo '-> Please Note: This program may work on this host but MATLAB will not!'
echo '----------------------------------------------------------------------------'
echo 'Please wait . . .'
echo ' '
#---------------------------------------------------------------------------
		        sleep 5
		    else
#---------------------------------------------------------------------------
echo ' '
#---------------------------------------------------------------------------
		    fi
		    ;;
                 *)
                    :
                    ;;
            esac
#
            case "$errtype" in
                'Unsupported'|'Unqualified')
#---------------------------------------------------------------------------
echo '   For system requirements consult http://www.mathworks.com ...'
#---------------------------------------------------------------------------
                    ;;
                'Internal')
#---------------------------------------------------------------------------
echo 'Please report this problem to The MathWorks, Inc. Technical Support'
echo '       phone: (508) 647-7000'
echo '       email: support@mathworks.com'
#---------------------------------------------------------------------------
                    ;;
                 *)
                    :
                    ;;
            esac
#
            case "$errtype" in
                'Unsupported'|'Unqualified'|'Internal')
#---------------------------------------------------------------------------
echo ' '
echo '***************************************************************************'
echo '-> Best to quit by pressing <return> at the next prompt ...'
echo ' '
echon '   Do you still want to try to continue? (y/[n]) > '
#---------------------------------------------------------------------------
                    if [ "$batch" != "1" ]; then
                        read ans
                        if [ `expr "//$ans" : '//[Yy].*'` -gt 0 ]; then
                            :
                        else
                            oscheck_status=1
                        fi
                    else
#---------------------------------------------------------------------------
     echo 'y'               
#---------------------------------------------------------------------------
                    fi
#---------------------------------------------------------------------------
echo ' '
#---------------------------------------------------------------------------
                    ;;
                 *)
                    :
                    ;;
            esac
	fi
    fi
    rm -f $temp_file
