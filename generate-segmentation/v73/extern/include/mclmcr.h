/*
 * @(#)mclmcr.h    generated by: makeheader 4.21  Tue Jul 26 23:11:50 2005
 *
 *		built from:	../../src/include/copyright.h
 *				../../src/include/pragma_interface.h
 *				./arraydata.cpp
 *				./arrayfactory.cpp
 *				./arrayref.cpp
 *				./charbuffer.cpp
 *				./mclcpp.cpp
 *				./mclmcr.cpp
 *				./mclmcrmcc.cpp
 *				./mwarray_common.cpp
 *				./objallocator.cpp
 *				mclcppExternC.cpp
 */

#ifndef mclmcr_h
#define mclmcr_h


/*
 * Copyright 1984-2003 The MathWorks, Inc.
 * All Rights Reserved.
 */



/* Copyright 2003-2004 The MathWorks, Inc. */

/*
 * Prevent g++ from making copies of vtable and typeinfo data
 * in every compilation unit.  By allowing for only one, we can
 * save space and prevent some situations where the linker fails
 * to coalesce them properly into a single entry.
 *
 * References:
 *    http://gcc.gnu.org/onlinedocs/gcc/Vague-Linkage.html#Vague%20Linkage
 *    http://gcc.gnu.org/onlinedocs/gcc/C---Interface.html
 */

#ifdef __cplusplus
#  ifdef __linux__
#    pragma interface
#  endif
#endif



#include <stdarg.h>
#include <string.h>
#include <wchar.h>
#include "matrix.h"


typedef void* HMCRINSTANCE;
typedef int (*mclOutputHandlerFcn)(const char *s);

/* Aggregate component-specific data.
 * Note: If you add fields here, make sure you update mclCreateComponentData
 * and mclDestroyComponentData.
 */
typedef struct mcl_component_data
{
    /* Key used to decrypt session key. This key has been encrypted with the
     * MCR's public key.
     */
    const unsigned char *public_data;

    /* Name of the component */
    const char *name_data;

    /* Root directory of the component (appended to the name of the 
     * CTF directory, if the root_data is non-NULL). Not used, I think.
     * TODO: Determine if this is used, and remove it if it isn't.
     */
    const char *root_data;

    /* Encrypted session key */
    const unsigned char *session_data;

    /* List of directories that will comprise the ENTIRE MATLAB path of the
     * application.
     */
    const char ** matlab_path_data;
    int matlab_path_data_count;

    /* List of directories that will comprise the ENTIRE Java class path 
     * of the application.
     */
    const char **classpath_data;
    int classpath_data_count;

    /* List of directories that will comprise the library load path
     * of the application.
     */
    const char **lib_path_data;
    int lib_path_data_count;

    /* MCR instance-specific options */
    const char **application_options;
    int application_option_count;
    
    /* Global (all MCR instances in this process) application options. */
    const char **runtime_options;
    int runtime_option_count;

    /* Directory in the CTF archive that contains the MATLAB preference
     * files.
     */
    const char *preferences_dir;

    /* Warning status: a list of warnings and their states (on or off).
     * For example, the string:
     *
     *    "off MCR:Extract"
     * 
     * means, turn the MCR:Extract warning off at the earliest possible time
     * during application initialization.
     */

    const char **set_warning_state;
    int set_warning_state_count;

    /* The directory where the component resides */
    const char *path_to_component;

} mclComponentData;

/* All the types of components we can generate code for. These values 
 * determine how the component initializes itself.
 */
typedef enum
{
    NoObjectType,
    COMObject,
    JavaObject,
    DotNetObject
} mccComponentType;

typedef enum {
  ExeTarget,
  LibTarget,
  MexTarget,
  SfunTarget,
  AnyTarget
} mccTargetType;



#ifdef __cplusplus
extern "C"
{
#endif


extern void mclEnableWarning(const char *warnID);


extern void mclDisableWarning(const char *warnID);

 
extern void mclSetErrorHandler(HMCRINSTANCE inst, mclOutputHandlerFcn eh);

 
extern void mclSetPrintHandler(HMCRINSTANCE inst, mclOutputHandlerFcn ph);


#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
    extern "C" {
#endif


extern const char *mclGetPathMacro(const char* macro);


extern void mclAddPathMacro(const char* macro, const char* expansion);


extern void mclRemovePathMacro(const char* macro);


#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
    extern "C" {
#endif


extern bool mclInitializeApplication(const char **options, int count);


extern int mclRunMain(int (*run_main)(int, const char **),
               int argc,
               const char **argv);


extern void mclSetExitCode(int code);


extern bool mclTerminateApplication(void);


extern void mclInhibitShutdown(void);


extern void mclUninhibitShutdown(void);


extern bool mclGetDispatcherPathID(HMCRINSTANCE inst, void **path);


extern bool mclWhich(HMCRINSTANCE inst, const char* name, char *path, int pathlen);


extern bool mclDirName(HMCRINSTANCE inst, const char* name, char *path,
		int pathlen);


extern bool mclIsDemoMCR(HMCRINSTANCE inst, bool *isdemo);


extern char **mclGetInstancePath(HMCRINSTANCE inst);


extern const char *mclGetInstanceCWD(HMCRINSTANCE inst);


extern bool mclSwapPath(char ***oldPath, char **old_cwd, char **newPath,
		 const char *current_directory);


extern bool mclChangeDirectory(HMCRINSTANCE inst, const char* dir);


extern bool mclChangeDirectoryFeval(HMCRINSTANCE inst, const char* dir);


extern bool mclAddPath(HMCRINSTANCE inst, const char* dirName);


extern bool mclRemovePath(HMCRINSTANCE inst, const char* dirName);


extern bool mclAddPath(HMCRINSTANCE inst, const char* dir);


extern mxArray *mclCreateCellArrayFromArrayList(int narray, mxArray *parray[]);

extern bool mclTerminateInstance(HMCRINSTANCE* inst);


extern bool mclPushActivation(HMCRINSTANCE inst);


extern bool mclPopActivation(HMCRINSTANCE inst);

extern const char* mclGetLastErrorMessage(HMCRINSTANCE inst);

extern const char* mclGetLastErrorCode(HMCRINSTANCE inst);

extern bool mclFeval(HMCRINSTANCE inst, const char* name, int nlhs, mxArray** plhs, int nrhs, mxArray** prhs);

extern bool mclMexFeval(HMCRINSTANCE inst, const char* name, int nlhs, mxArray** plhs, int nrhs, const mxArray** prhs);

extern bool mclMlfVFeval(HMCRINSTANCE inst, const char* name, int nargout, int fnout, int fnin, va_list ap);

extern bool mclMlfFeval(HMCRINSTANCE inst, const char* name, int nargout, int fnout, int fnin, ...);

 
extern mclComponentData *mclCreateComponentData(
    unsigned char *public_data, char *name_data, char *root_data,
    unsigned char *session_data,
    char **matlab_path_data, int matlab_path_data_count,
    char **classpath_data, int classpath_data_count,
    char **lib_path_data, int lib_path_data_count,
    char **application_options, int application_option_count,
    char **runtime_options, int runtime_option_count,
    char *prefdir,
    const char *path_to_component,
    char **warning_state, int warning_state_count);


extern void mclDestroyComponentData(mclComponentData *cdata);


extern bool mclInitializeComponentInstance(HMCRINSTANCE* inst,
				    const mclComponentData *cdata,
				    bool replace_path,
				    mccComponentType ctype,
				    mccTargetType ttype,
				    mclOutputHandlerFcn error_handler,
				    mclOutputHandlerFcn print_handler);

extern int mclMain(HMCRINSTANCE inst, int argc, const char* argv[],
		      const char* name, int nlhs);


extern void mclWaitForFiguresToDie(HMCRINSTANCE inst);


extern mxArray* mclCreateSharedCopy(mxArray* px);


extern bool mclSetGlobal(HMCRINSTANCE inst, const char* name, mxArray* px);


extern bool mclGetGlobal(HMCRINSTANCE inst, const char* name, mxArray** ppx);


extern mxArray* mclCreateEmptyArray(void);

 
extern int mclGetMaxPathLen(void);

 
extern int mclGetDotNetComponentType(void);

 
extern int mclGetMCCTargetType(bool isLibrary);


extern mxArray* mclCreateSimpleFunctionHandle(mxFunctionPtr fcn);


extern bool mclRegisterExternalFunction(HMCRINSTANCE inst, const char* varname, mxFunctionPtr fcn);


extern int mclGetID(HMCRINSTANCE inst);


extern int mclGetActiveID(void);


extern bool mclmcrInitialize(void);



#ifdef _WIN32
#ifdef _WIN64
typedef int int32_t;
#else
typedef long int32_t;
#endif
#endif

#ifndef __ICUEXT_HAS_FEATURE_WG14_EXTENDED_CHAR_TYPEDEFS__

#ifndef __STDC_UTF_16__
#ifdef _WIN32
typedef wchar_t char16_t;
#else
typedef UINT16_T char16_t;
#endif
#endif

#endif

#define MAX_FIELD_NAME_SIZE 1024


typedef struct _wcsStackPointer
{
  char16_t * hPtr;
  char16_t   sPtr[MAX_FIELD_NAME_SIZE];
  int32_t buffLen;
} *pwcsStackPointer;


extern void initializeWcsStackPointer(pwcsStackPointer *ptr);


extern void deleteWcsStackPointer(pwcsStackPointer ptr);


extern int mwMbstowcs( pwcsStackPointer sp, const char *sourceString);


extern void utf16_to_lcp_n_fcn(char * target, int32_t * targetSize,
                    char16_t const * source, int32_t sourceSize);


extern int32_t utf16_strlen_fcn(char16_t const * s);


extern char16_t * utf16_strncpy_fcn(char16_t * dst, char16_t const * src, int32_t n);


extern char16_t * utf16_strdup_fcn(const char16_t * sl);


/* Extract the path from a file name specified by either absolute or
 * relative path. For example:
 *
 *   /home/foo/bar.exe -> /home/foo
 *   ./bar.exe -> <full path to cwd>/bar.exe
 *   bar.exe -> <empty string>
 *
 * Returns a newly allocated string, which you must free or leak.
 */
extern char* separatePathName(const char *fullname);


#ifdef __cplusplus
}
#endif



#include <stdarg.h>
#include "matrix.h"

typedef real64_T mxDouble;
typedef real32_T mxSingle;
typedef int8_T mxInt8;
typedef uint8_T mxUint8;
typedef int16_T mxInt16;
typedef uint16_T mxUint16;
typedef int32_T mxInt32;
typedef uint32_T mxUint32;
#if !defined(__MW_STDINT_H__)
#  if defined( linux ) || defined( __linux ) || defined( __linux__ )
#    include <stdint.h>
     typedef int64_t mxInt64;
     typedef uint64_t mxUint64;
#  elif defined( macintosh ) || defined( __APPLE__ ) || defined( __APPLE_CC__ )
#    if defined( __GNUC__ )
#      include <stdint.h>
       typedef int64_t mxInt64;
       typedef uint64_t mxUint64;
#    endif
#  elif defined( sun ) || defined( __sun )
#    include <inttypes.h>
     typedef int64_t mxInt64;
     typedef uint64_t mxUint64;
#  elif defined( __hpux )
#    include <inttypes.h>
     typedef int64_t mxInt64;
     typedef uint64_t mxUint64;
#  elif defined(_MSC_VER)
     typedef __int64 mxInt64;
     typedef unsigned __int64 mxUint64;
#  elif defined(__BORLANDC__)
     typedef __int64 mxInt64;
     typedef unsigned __int64 mxUint64;
#  elif defined(__WATCOMC__)
     typedef __int64 mxInt64;
     typedef unsigned __int64 mxUint64;
#  elif defined(__LCC__)
     typedef __int64 mxInt64;
     typedef unsigned __int64 mxUint64;
#  endif
#else
   typedef int64_T mxInt64;
   typedef uint64_T mxUint64;
#endif



#define MCLCPP_OK    0
#define MCLCPP_ERR  -1


#ifdef __cplusplus
    extern "C" {
#endif


extern void mclAcquireMutex(void);


extern void mclReleaseMutex(void);


#ifdef __cplusplus
    }
#endif



#ifdef __cplusplus

// Defines error_info, array_buffer, array_ref and char_buffer
#include "mclcppAPI.h"
#include "mclcppExternC.h"

#endif




#ifdef __cplusplus

class mwLock
{
public:
    mwLock()
    {
        mclAcquireMutex();
    }
    virtual ~mwLock()
    {
        mclReleaseMutex();
    }
};

#endif



#ifdef __cplusplus
    extern "C" {
#endif


extern int mclcppGetLastError(void** ppv);


extern int mclcppCreateError(void** ppv, const char* msg);


extern void mclcppSetLastError(const char* msg);


extern int mclcppErrorCheck(void);


#ifdef __cplusplus
    }
#endif



#ifdef __cplusplus

#include <iostream>
#include <exception>

class mwException : public std::exception
{
public:
    mwException() : std::exception()
    {
        m_err = 0;
        mclcppCreateError((void**)&m_err, "Unspecified error");
    }
    mwException(const char* msg) : std::exception()
    {
        m_err = 0;
        mclcppCreateError((void**)&m_err, (msg ? msg : "Unspecified error"));
    }
    mwException(const mwException& e) : std::exception()
    {
        m_err = e.m_err;
        if (m_err)
            ref_count_obj_addref(m_err);
    }
    mwException(error_info* pe)
    {
        m_err = 0;
        if (pe)
        {
            m_err = pe;
            ref_count_obj_addref(m_err);
        }
        else
        {
            mclcppCreateError((void**)&m_err, "Unspecified error");
        }
    }
    mwException(error_info* pe, bool bAddRef)
    {
        m_err = 0;
        if (pe)
        {
            m_err = pe;
            if (bAddRef)
                ref_count_obj_addref(m_err);
        }
        else
        {
            mclcppCreateError((void**)&m_err, "Unspecified error");
        }
    }
    mwException(const std::exception& e) : std::exception()
    {
        m_err = 0;
        mclcppCreateError((void**)&m_err, e.what());
    }
    virtual ~mwException() throw()
    {
        if (m_err)
            ref_count_obj_release(m_err);
    }
    mwException& operator=(const std::exception& e)
    {
        if (m_err)
            ref_count_obj_release(m_err);
        mclcppCreateError((void**)&m_err, e.what());
        return *this;
    }
    mwException& operator=(const mwException& e)
    {
        if (m_err)
            ref_count_obj_release(m_err);
        m_err = e.m_err;
        if (m_err)
            ref_count_obj_addref(m_err);
        return *this;
    }
    const char *what() const throw()
    {
        return (m_err ? error_info_get_message(m_err) : NULL);
    }
    static void raise_error()
    {
        error_info* pe = 0;
        if (mclcppGetLastError((void**)&pe) == MCLCPP_ERR)
	{
	    throw mwException();
	}
        throw mwException(pe, false);
    }
    static void check_raise_error()
    {
        if (!mclcppErrorCheck())
            return;
        mwException::raise_error();
    }
protected:
    error_info* m_err;
};

#endif




#ifdef __cplusplus

template<typename T>
class mw_auto_ptr_t
{
public:
    mw_auto_ptr_t()
    {
        m_p = 0;
    }
    explicit mw_auto_ptr_t(T* p)
    {
        m_p = p;
        addref();
    }
    mw_auto_ptr_t(T*p, bool bAddRef)
    {
        m_p = p;
        if (bAddRef)
            addref();
    }
    virtual ~mw_auto_ptr_t()
    {
        if (m_p)
	    ref_count_obj_release(m_p);
    }
    void addref()
    {
        if (m_p)
	    ref_count_obj_addref(m_p);
    }
    void release()
    {
        if (m_p)
        {
	    ref_count_obj_release(m_p);
            m_p = 0;
        }
    }
    void attach(T* p, bool bAddRef)
    {
        release();
        m_p = p;
        if (bAddRef)
            addref();
    }
    T* detach()
    {
        T* p = m_p;
        m_p = 0;
        return p;
    }
    T* operator->(void) const
    {
        if (!m_p)
            throw mwException("Null pointer");
        return m_p;
    }
    T** operator&(void)
    {
        release();
        return &m_p;
    }
    operator T*() const
    {
        return m_p;
    }
    mw_auto_ptr_t<T>& operator=(T* p)
    {
        release();
        m_p = p;
        addref();
        return *this;
    }
    mw_auto_ptr_t<T>& operator=(const mw_auto_ptr_t<T>& ptr)
    {
        release();
        m_p = ptr.m_p;
        addref();
        return *this;
    }
    bool operator!() const
    {
        return (m_p == 0);
    }
    operator bool() const
    {
        return (m_p != 0);
    }
    bool operator==(const mw_auto_ptr_t<T>& ptr)
    {
        return (m_p == (T*)ptr);
    }
    bool operator!=(const mw_auto_ptr_t<T>& ptr)
    {
        return (m_p != (T*)ptr);
    }
protected:
    T* m_p;
};

#endif /* ifdef  __cplusplus */



#ifdef __cplusplus
    extern "C" {
#endif


extern int mclCreateCharBuffer(void** ppv, const char* str);


#ifdef __cplusplus
    }
#endif



#ifdef __cplusplus

//#include <iostream>

class mwString
{
public:
    mwString()
    {
        if (mclCreateCharBuffer((void**)&m_str, "") == MCLCPP_ERR)
            mwException::raise_error();
    }
    mwString(const char* str)
    {
        if (mclCreateCharBuffer((void**)&m_str, str) == MCLCPP_ERR)
            mwException::raise_error();
    }
    mwString(char_buffer* buff, bool bAddref)
    {
	m_str.attach(buff, bAddref);
    }
    mwString(const mwString& str)
    {
        if (mclCreateCharBuffer((void**)&m_str, str) == MCLCPP_ERR)
            mwException::raise_error();
        if (char_buffer_set_buffer(m_str, (const char*)str) == MCLCPP_ERR)
            mwException::raise_error();
    }
    virtual ~mwString(){}
public:
    int Length() const
    {
        return char_buffer_size(m_str);
    }
    operator const char* () const
    {
        return char_buffer_get_buffer(m_str);
    }
    mwString& operator=(const mwString& str)
    {
        if (&str == this)
            return *this;
        if (char_buffer_set_buffer(m_str, (const char*)str) == MCLCPP_ERR)
            mwException::raise_error();
        return *this;
    }
    mwString& operator=(const char* str)
    {
        if (char_buffer_set_buffer(m_str, str) == MCLCPP_ERR)
            mwException::raise_error();
        return *this;
    }
    bool operator==(const mwString& str) const
    {
        return (char_buffer_compare_to(m_str, str.m_str) == 0);
    }
    bool operator!=(const mwString& str) const
    {
        return (char_buffer_compare_to(m_str, str.m_str) != 0);
    }
    bool operator<(const mwString& str) const
    {
        return (char_buffer_compare_to(m_str, str.m_str) < 0);
    }
    bool operator<=(const mwString& str) const
    {
        return (char_buffer_compare_to(m_str, str.m_str) <= 0);
    }
    bool operator>(const mwString& str) const
    {
        return (char_buffer_compare_to(m_str, str.m_str) > 0);
    }
    bool operator>=(const mwString& str) const
    {
        return (char_buffer_compare_to(m_str, str.m_str) >= 0);
    }
    friend std::ostream& operator<<(std::ostream& os, const mwString& str)
    {
        os << (const char*)str;
        return os;
    }
private:
    mw_auto_ptr_t<char_buffer> m_str;
};

#endif



#ifdef __cplusplus
    extern "C" {
#endif


extern double mclGetEps(void);


extern double mclGetInf(void);


extern double mclGetNaN(void);


extern bool mclIsFinite(double x);


extern bool mclIsInf(double x);


extern bool mclIsNaN(double x);


extern int mclGetEmptyArray(void** ppv, mxClassID classid);


extern int mclGetMatrix(void** ppv, int num_rows, int num_cols, mxClassID classid, mxComplexity cmplx);


extern int mclGetArray(void** ppv, int num_dims, const int* dims, mxClassID classid, mxComplexity cmplx);


extern int mclGetNumericMatrix(void** ppv, int num_rows, int num_cols, mxClassID mxID, mxComplexity cmplx);


extern int mclGetNumericArray(void** ppv, int num_dims, const int* dims, mxClassID mxID, mxComplexity cmplx);


extern int mclGetScalarDouble(void** ppv, mxDouble re, mxDouble im, mxComplexity cmplx);


extern int mclGetScalarSingle(void** ppv, mxSingle re, mxSingle im, mxComplexity cmplx);


extern int mclGetScalarInt8(void** ppv, mxInt8 re, mxInt8 im, mxComplexity cmplx);


extern int mclGetScalarUint8(void** ppv, mxUint8 re, mxUint8 im, mxComplexity cmplx);


extern int mclGetScalarInt16(void** ppv, mxInt16 re, mxInt16 im, mxComplexity cmplx);


extern int mclGetScalarUint16(void** ppv, mxUint16 re, mxUint16 im, mxComplexity cmplx);


extern int mclGetScalarInt32(void** ppv, mxInt32 re, mxInt32 im, mxComplexity cmplx);


extern int mclGetScalarUint32(void** ppv, mxUint32 re, mxUint32 im, mxComplexity cmplx);


extern int mclGetScalarInt64(void** ppv, mxInt64 re, mxInt64 im, mxComplexity cmplx);


extern int mclGetScalarUint64(void** ppv, mxUint64 re, mxUint64 im, mxComplexity cmplx);


extern int mclGetCharMatrix(void** ppv, int num_rows, int num_cols);


extern int mclGetCharArray(void** ppv, int num_dims, const int* dims);


extern int mclGetScalarChar(void** ppv, mxChar x);


extern int mclGetString(void** ppv, const char* str);


extern int mclGetCharMatrixFromStrings(void** ppv, int m, const char** str);


extern int mclGetLogicalMatrix(void** ppv, int num_rows, int num_cols);


extern int mclGetLogicalArray(void** ppv, int num_dims, const int* dims);


extern int mclGetScalarLogical(void** ppv, mxLogical x);


extern int mclGetCellMatrix(void** ppv, int num_rows, int num_cols);


extern int mclGetCellArray(void** ppv, int num_dims, const int* dims);


extern int mclGetStructMatrix(void** ppv, int num_rows, int num_cols, int nFields, const char** fieldnames);


extern int mclGetStructArray(void** ppv, int num_dims, const int* dims, int nFields, const char** fieldnames);


extern int mclGetNumericSparse(void** ppv, int data_size, const int* rowindex, const int* colindex, const void* rData,
                        const void* iData, int num_rows, int num_cols, int nzmax, mxClassID mxType, mxComplexity cmplx);


extern int mclGetLogicalSparse(void** ppv, int data_size, const int* rowindex, const int* colindex, const mxLogical* rData,
                        int num_rows, int num_cols, int nzmax);


extern int mclDeserializeArray(void** ppv, void** ppa);


extern int mclcppGetArrayBuffer(void** ppv, int size);


extern int mclcppFeval(HMCRINSTANCE inst, const char* name, int nargout, void** lhs, void* rhs);


extern int mclcppArrayToString(const mxArray* parray, char** ppstr);


#ifdef __cplusplus
    }
#endif


#ifdef __cplusplus
    extern "C" {
#endif

extern bool mclInitializeInstance(HMCRINSTANCE* inst);


#ifdef __cplusplus
    }
#endif


#ifdef __cplusplus
extern "C" {
/* This is an extern "C" API exclusively for use by C++ programs. It
 * exists solely to work around binary incompatibilities between different
 * C++ compilers. For example, a Borland C++ program cannot invoke a method
 * on an array_ref object created by a library compiled with Microsoft Visual 
 * C++. The mwArray API, therefore, invokes array_ref methods indirectly, by
 * passing the array_ref object to one of these extern "C" routines, which
 * are implemented in the MCLMCR module. Since this module is part of the
 * MCR, it can invoke array_ref methods with impunity.
 *
 * This API needs to be protected by #ifdef __cplusplus because some of the
 * input arguments to the functions it contains are pointers to objects.
 * Translating all of these to void *'s is overly complex and unnecessary,
 * as this API is always going to be called from a C++ program.
 */



extern int ref_count_obj_addref(ref_count_obj *obj);


extern int ref_count_obj_release(ref_count_obj *obj);


extern int char_buffer_size(char_buffer *obj);


extern const char* char_buffer_get_buffer(char_buffer *obj);


extern int char_buffer_set_buffer(char_buffer *obj, const char* str);


extern int char_buffer_compare_to(char_buffer *obj, char_buffer* p);


extern mxClassID array_ref_classID(array_ref *obj);


extern array_ref* array_ref_deep_copy(array_ref *obj);


extern array_ref* array_ref_shared_copy(array_ref *obj);


extern array_ref* array_ref_serialize(array_ref *obj);


extern int array_ref_element_size(array_ref *obj);


extern int array_ref_number_of_elements(array_ref *obj);


extern int array_ref_number_of_nonzeros(array_ref *obj);


extern int array_ref_maximum_nonzeros(array_ref *obj);


extern int array_ref_number_of_dimensions(array_ref *obj);


extern array_ref* array_ref_get_dimensions(array_ref *obj);


extern int array_ref_number_of_fields(array_ref *obj);


extern char_buffer* array_ref_get_field_name(array_ref *obj, int i);


extern bool array_ref_is_empty(array_ref *obj);


extern bool array_ref_is_sparse(array_ref *obj);


extern bool array_ref_is_numeric(array_ref *obj);


extern bool array_ref_is_complex(array_ref *obj);


extern int array_ref_make_complex(array_ref *obj);


extern bool array_ref_equals(array_ref *obj, array_ref* p);


extern int array_ref_compare_to(array_ref *obj, array_ref* p);


extern int array_ref_hash_code(array_ref *obj);


extern char_buffer* array_ref_to_string(array_ref *obj);


extern array_ref* array_ref_row_index(array_ref *obj);


extern array_ref* array_ref_column_index(array_ref *obj);


extern array_ref* array_ref_get_int(array_ref *obj, int num_indices, const int* index);


extern array_ref* array_ref_get_const_char(array_ref *obj, const char* name, int num_indices, const int* index);


extern array_ref* array_ref_getV_int(array_ref *obj, int num_indices, va_list vargs);


extern array_ref* array_ref_getV_const_char(array_ref *obj, const char* name, int num_indices, va_list vargs);


extern int array_ref_set(array_ref *obj, array_ref* p);


extern array_ref* array_ref_real(array_ref *obj);


extern array_ref* array_ref_imag(array_ref *obj);


extern int array_ref_get_numeric_mxDouble(array_ref *obj, mxDouble* x, int len);


extern int array_ref_get_numeric_mxSingle(array_ref *obj, mxSingle* x, int len);


extern int array_ref_get_numeric_mxInt8(array_ref *obj, mxInt8* x, int len);


extern int array_ref_get_numeric_mxUint8(array_ref *obj, mxUint8* x, int len);


extern int array_ref_get_numeric_mxInt16(array_ref *obj, mxInt16* x, int len);


extern int array_ref_get_numeric_mxUint16(array_ref *obj, mxUint16* x, int len);


extern int array_ref_get_numeric_mxInt32(array_ref *obj, mxInt32* x, int len);


extern int array_ref_get_numeric_mxUint32(array_ref *obj, mxUint32* x, int len);


extern int array_ref_get_numeric_mxInt64(array_ref *obj, mxInt64* x, int len);


extern int array_ref_get_numeric_mxUint64(array_ref *obj, mxUint64* x, int len);


extern int array_ref_get_char(array_ref *obj, mxChar* x, int len);


extern int array_ref_get_logical(array_ref *obj, mxLogical* x, int len);


extern int array_ref_set_numeric_mxDouble(array_ref *obj, const mxDouble* x, int len);


extern int array_ref_set_numeric_mxSingle(array_ref *obj, const mxSingle* x, int len);


extern int array_ref_set_numeric_mxInt8(array_ref *obj, const mxInt8* x, int len);


extern int array_ref_set_numeric_mxUint8(array_ref *obj, const mxUint8* x, int len);


extern int array_ref_set_numeric_mxInt16(array_ref *obj, const mxInt16* x, int len);


extern int array_ref_set_numeric_mxUint16(array_ref *obj, const mxUint16* x, int len);


extern int array_ref_set_numeric_mxInt32(array_ref *obj, const mxInt32* x, int len);


extern int array_ref_set_numeric_mxUint32(array_ref *obj, const mxUint32* x, int len);


extern int array_ref_set_numeric_mxInt64(array_ref *obj, const mxInt64* x, int len);


extern int array_ref_set_numeric_mxUint64(array_ref *obj, const mxUint64* x, int len);


extern int array_ref_set_char(array_ref *obj, const mxChar* x, int len);


extern int array_ref_set_logical(array_ref *obj, const mxLogical* x, int len);


extern int array_buffer_size(array_buffer *obj);


extern array_ref* array_buffer_get(array_buffer *obj, int offset);


extern int array_buffer_set(array_buffer *obj, int offset, array_ref* p);


extern int array_buffer_add(array_buffer *obj, array_ref* pa);


extern int array_buffer_remove(array_buffer *obj, int offset);


extern int array_buffer_clear(array_buffer *obj);


extern array_ref* array_buffer_to_cell(array_buffer *obj, int offset, int len);


extern const char* error_info_get_message(error_info *obj);


/* End ifdef __cplusplus */

}
#endif

#endif /* mclmcr_h */
