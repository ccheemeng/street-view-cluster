#!/bin/sh
#
# usage:        arch.sh
#
# abstract:     This Bourne Shell script determines the architecture
#		of the the current machine.
#
#		ARCH	  - Machine architecture
#
#		IMPORTANT: The shell function 'check_archlist' is used
#			   by this routine and MUST be loaded first.
#			   This can be done by sourcing the file,
#
#			       archlist.sh
#
#			   before using this routine.
#
# note(s):	1. This routine must be called using a . (period)
#
#		2. Also returns ARCH_MSG which may contain additional
#		   information when ARCH returns 'unknown'.
#
# Copyright 1986-2004 The MathWorks, Inc.
# $Revision: 1.17.4.5 $  $Date: 2004/07/08 01:06:09 $
#----------------------------------------------------------------------------
#
#=======================================================================
# Functions:
#   realfilepath ()
#   matlab6_arch ()
#=======================================================================
    realfilepath () { # Returns the actual path in the file system
		      # of a file. It follows links. It returns an
		      # empty path if an error occurs.
		      #
                      # Returns a 1 status if the file does not exist
		      # or appears to be a circular link. Otherwise, 
		      # a 0 status is returned. 
                      #
                      # usage: realfilepath filepath
                      #
	file=$1
	n=1
#
	dir=`dirname $file`
	dir=`(cd $dir; /bin/pwd)`
 	file=`basename $file`
#
# Try up to 8 links
#
    	while [ $n -le 8 ]
    	do
	    (cd $dir) >/dev/null 2>&1
	    if [ $? -eq 0 ]; then
	        lscmd=`(cd $dir; ls -l $file 2>/dev/null)`
#
# Check for link portably
#
                if [ `expr "//$lscmd" : '//.*->.*'` -ne 0 ]; then
                    link=`echo "$lscmd" | awk '{ print $NF }'`
		    dirnext=`dirname $link`
		    dir=`(cd $dir; cd $dirnext; /bin/pwd)`
		    file=`basename $link`
                elif [ "$lscmd" != "" ]; then
	            echo `(cd $dir; /bin/pwd)`/$file
	            return 0
	        else
		    return 1
	        fi
	    else
		return 1
	    fi
	    n=`expr $n + 1`
        done
	return 1
    }
#
#=======================================================================
    matlab6_arch () { # Determine the architecture for MATLAB 6.x
		      # It returns the value in the ARCH variable.
		      # If 'unknown' is returned then sometimes a
		      # diagnostic message is returned in ARCH_MSG.
                      #
                      # Always returns a 0 status.
                      #
                      # usage: matlab6_arch
                      #
	ARCH="unknown"
#
	if [ -f /bin/uname ]; then
   	    case "`/bin/uname`" in
	        SunOS)					# sol2
	            if [ -d /dev/pts ]; then
		        ARCH="sol2"
	            fi
	            ;;
	        HP-UX)					# hp 700 & 800
		    majorversion=`/bin/uname -r | awk '
#-----------------------------------------------------------------------
			{ split(substr($1,3),a,"."); print a[1] }'`
#-----------------------------------------------------------------------
	            if [ -f /bin/hp9000s700 ]; then
		        (/bin/hp9000s700) > /dev/null 2>&1
		        if [ $? -eq 0 ]; then
			    if [ $majorversion -lt 11 ]; then
	    	                ARCH="hp700"
			    else
				ARCH="hpux"
			    fi
		        fi
	            fi
	            if [ -f /bin/hp9000s800 ]; then
		        (/bin/hp9000s800) > /dev/null 2>&1
		        if [ $? -eq 0 ]; then
			    if [ $majorversion -lt 11 ]; then
	    	                ARCH="hp700"
			    else
				ARCH="hpux"
			    fi
		        fi
	            fi
	            ;;
	        IRIX|IRIX64)				# sgi
    	            if [ -f /bin/4d ]; then
		        (/bin/4d) > /dev/null 2>&1
		        if [ $? -eq 0 ]; then
		            if [ -f /bin/hinv ]; then
			        ARCH_MSG=`/bin/hinv | awk '
#-----------------------------------------------------------------------
# If we want -mips4 -n32. Must be cpu >= 5000
# If we want -mips3 -n32. Must be cpu >= 4000
#
	$1 == "CPU:" { cpu = substr($3,2) + 0
		       if (cpu < 5000)
#-----------------------------------------------------------------------
print "Appears to be sgi: But processor must be at least a R5000 ..."
#-----------------------------------------------------------------------
		     }'`
#-----------------------------------------------------------------------
			        if [ "$ARCH_MSG" = "" ]; then
			            ARCH=sgi
			        fi
			    else
#-----------------------------------------------------------------------
ARCH_MSG='Appears to be sgi: But processor could not be determined ...'
#-----------------------------------------------------------------------
			    fi
			fi
		    fi
	            ;;
	        OSF1)					# alpha
	    	    ARCH="alpha"
	            ;;
	        AIX*)					# ibm_rs
#
# With AIX 4.1, uname can return more than just 'AIX'
#
	            ARCH="ibm_rs"
	            ;;
	        Linux)
		    case "`/bin/uname -m`" in
		    i*86)
			ARCH="glnx86"
			;;
		    ia64)
			ARCH="glnxi64"
			;;
		    x86_64)
			ARCH="glnxa64"
			;;
		    esac
		    ;;
# Usually uname lives in /usr/bin on the Mac, but sometimes people 
# have links in /bin that link uname to /usr/bin.  Because of this
# Mac needs to be listed in the checks for both /bin/uname and /usr/bin/uname
	        Darwin)					# Mac OS X
                    ARCH="mac"
                    ;;
	        *)
		    :
	            ;;
	    esac
	elif [ -f /usr/bin/uname ]; then
   	    case "`/usr/bin/uname`" in
	        Darwin)					# Mac OS X
                    ARCH="mac"
                    ;;
            esac
        fi
	return 0
    }
#=======================================================================
#
# The local shell function check_archlist is assume to be loaded before this
# function is sourced.
#
    ARCH_MSG=''
    check_archlist ARCH=$ARCH
    if [ "$ARCH" = "" ]; then
	if [ "$MATLAB_ARCH" != "" ]; then
	    check_archlist MATLAB_ARCH=$MATLAB_ARCH
	fi
	if [ "$ARCH" = "" ]; then
	    matlab6_arch
	fi
    fi
    Arch=$ARCH
