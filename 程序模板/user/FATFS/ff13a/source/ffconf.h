/*---------------------------------------------------------------------------/
/  FatFs - Configuration file
/---------------------------------------------------------------------------*/

#define FFCONF_DEF 89352	/* Revision ID */

/*---------------------------------------------------------------------------/
/ Function Configurations
/---------------------------------------------------------------------------*/

#define FF_FS_READONLY	0
/* This option switches read-only configuration. (0:Read/Write or 1:Read-only)
/  Read-only configuration removes writing API functions, f_write(), f_sync(),
/  f_unlink(), f_mkdir(), f_chmod(), f_rename(), f_truncate(), f_getfree()
/  and optional writing functions as well. */
//0:可读可写  1：只读，还将删除一些函数

#define FF_FS_MINIMIZE	0
/* This option defines minimization level to remove some basic API functions.
/
/   0: Basic functions are fully enabled.
/   1: f_stat(), f_getfree(), f_unlink(), f_mkdir(), f_truncate() and f_rename()
/      are removed.    这些函数将被移除
/   2: f_opendir(), f_readdir() and f_closedir() are removed in addition to 1.
/   3: f_lseek() function is removed in addition to 2. */
//设置不同的值，删除裁剪的程度不同，如果是0的话就表示应用所有函数

#define FF_USE_STRFUNC	1
/* This option switches string functions, f_gets(), f_putc(), f_puts() and f_printf().
/
/  0: Disable string functions.              //失能
/  1: Enable without LF-CRLF conversion.     //使能但是没有LF-CRLF转换
/  2: Enable with LF-CRLF conversion. */	 //使能


#define FF_USE_FIND		0
/* This option switches filtered directory read functions, f_findfirst() and
/  f_findnext(). (0:Disable, 1:Enable 2:Enable with matching altname[] too) */
//此选项切换筛选的目录读取功能

#define FF_USE_MKFS		1
/* This option switches f_mkfs() function. (0:Disable or 1:Enable) */
//f_mkfs函数的使能。(0:禁用或1:启用)

#define FF_USE_FASTSEEK	1
/* This option switches fast seek function. (0:Disable or 1:Enable) */
//快速索引特色的支持。(0:禁用或1:启用)

#define FF_USE_EXPAND	0
/* This option switches f_expand function. (0:Disable or 1:Enable) */
//该选项切换f_expand函数。(0:禁用或1:启用)

#define FF_USE_CHMOD	0
/* This option switches attribute manipulation functions, f_chmod() and f_utime().
/  (0:Disable or 1:Enable) Also FF_FS_READONLY needs to be 0 to enable this option. */
//该选项切换属性操作函数f_chmod()和f_utime()。(0:Disable或1:Enable) FF_FS_READONLY也需要为0才能启用该选项。

#define FF_USE_LABEL	0
/* This option switches volume label functions, f_getlabel() and f_setlabel().
/  (0:Disable or 1:Enable) */
//该选项切换卷标函数f_getlabel()和f_setlabel()。(0:Disable或1:Enable)

#define FF_USE_FORWARD	0
/* This option switches f_forward() function. (0:Disable or 1:Enable) */
//该选项切换f_forward()函数。(0:禁用或1:启用)

/*---------------------------------------------------------------------------/
/ Locale and Namespace Configurations
/---------------------------------------------------------------------------*/

#define FF_CODE_PAGE	936
/* This option specifies the OEM code page to be used on the target system.
/  Incorrect code page setting can cause a file open failure.
/
/   437 - U.S.
/   720 - Arabic
/   737 - Greek
/   771 - KBL
/   775 - Baltic
/   850 - Latin 1
/   852 - Latin 2
/   855 - Cyrillic
/   857 - Turkish
/   860 - Portuguese
/   861 - Icelandic
/   862 - Hebrew
/   863 - Canadian French
/   864 - Arabic
/   865 - Nordic
/   866 - Russian
/   869 - Greek 2
/   932 - Japanese (DBCS)
/   936 - Simplified Chinese (DBCS)
/   949 - Korean (DBCS)
/   950 - Traditional Chinese (DBCS)
/     0 - Include all code pages above and configured by f_setcp()
*/


#define FF_USE_LFN		0
#define FF_MAX_LFN		255
/* The FF_USE_LFN switches the support for LFN (long file name).
/
/   0: Disable LFN. FF_MAX_LFN has no effect.
/   0：不支持长文件名，MAX_LEN和LFN_UNICODE不影响
/   1: Enable LFN with static working buffer on the BSS. Always NOT thread-safe.
/	1：在BSS的静态缓冲区上对长文件名的支持，总是不可重入的
/   2: Enable LFN with dynamic working buffer on the STACK.
/	2：在堆栈的动态缓冲区上对长文件名的支持
/   3: Enable LFN with dynamic working buffer on the HEAP.
/	3：在堆的动态缓冲区上对长文件名支持
/
/  To enable the LFN, ffunicode.c needs to be added to the project. The LFN function
/  requiers certain internal working buffer occupies (FF_MAX_LFN + 1) * 2 bytes and
/  additional (FF_MAX_LFN + 44) / 15 * 32 bytes when exFAT is enabled.
/  The FF_MAX_LFN defines size of the working buffer in UTF-16 code unit and it can
/  be in range of 12 to 255. It is recommended to be set 255 to fully support LFN
/  specification.
/  	要启用LFN，需要将ffunicode.c添加到项目中。LFN函数
/	需要一定的内部工作缓冲区占用(FF_MAX_LFN + 1) * 2字节和
/	额外的(FF_MAX_LFN + 44) / 15 * 32字节时，exFAT是启用的。
/ 	FF_MAX_LFN在UTF-16代码单元中定义工作缓冲区的大小，它可以
/	范围在12到255之间。建议将其设置为255以完全支持LFN规范。
/  When use stack for the working buffer, take care on stack overflow. When use heap
/  memory for the working buffer, memory management functions, ff_memalloc() and
/  ff_memfree() in ffsystem.c, need to be added to the project. 
/	使用堆栈作为工作缓冲区时，请注意堆栈溢出。当使用堆
/	内存的工作缓冲区，内存管理功能，ff_memalloc()和
/ 	ff_memfree()在ffsystem.c中，需要将ffsystem.c添加到项目中。*/

#define FF_LFN_UNICODE	0
/* This option switches the character encoding on the API when LFN is enabled.
/
/   0: ANSI/OEM in current CP (TCHAR = char)
/   1: Unicode in UTF-16 (TCHAR = WCHAR)
/   2: Unicode in UTF-8 (TCHAR = char)
/
/  Also behavior of string I/O functions will be affected by this option.
/  When LFN is not enabled, this option has no effect. */
// FatFs API要切换字符编码形式为Union时，将LEN和LFN_UNICODE为1


#define FF_LFN_BUF		255
#define FF_SFN_BUF		12
/* This set of options defines size of file name members in the FILINFO structure
/  which is used to read out directory items. These values should be suffcient for
/  the file names to read. The maximum possible length of the read file name depends
/  on character encoding. When LFN is not enabled, these options have no effect. */
/*这组选项定义了FILINFO结构中文件名成员的大小用来读出目录项。这些值应该足够了
/要读取的文件名。读取文件名的最大可能长度取决于关于字符编码。当LFN未启用时，这些选项无效。*/


#define FF_STRF_ENCODE	3
/* When FF_LFN_UNICODE >= 1 with LFN enabled, string I/O functions, f_gets(),
/  f_putc(), f_puts and f_printf() convert the character encoding in it.
/  This option selects assumption of character encoding ON THE FILE to be
/当FF_LFN_UNICODE >= 1启用LFN时，字符串I/O函数，f_gets()，f_putc()、f_puts和f_printf()转换其中的字符编码。
/此选项选择文件上的字符编码假设通过那些功能读/写。
/   0: ANSI/OEM in current CP
/   1: Unicode in UTF-16LE
/   2: Unicode in UTF-16BE
/   3: Unicode in UTF-8          //编码格式
*/



#define FF_FS_RPATH		0
/* This option configures support for relative path.
/
/   0: Disable relative path and remove related functions.
/   1: Enable relative path. f_chdir() and f_chdrive() are available.
/   2: f_getcwd() function is available in addition to 1.
*/
//注意！f_readdir函数的输出受此项配置的影响

/*---------------------------------------------------------------------------/
/ Drive/Volume Configurations
/ 物理驱动配置
/---------------------------------------------------------------------------*/

#define FF_VOLUMES		1	//支持的物理设备数量
/* Number of volumes (logical drives) to be used. (1-10) */


#define FF_STR_VOLUME_ID	0
#define FF_VOLUME_STRS		"RAM","NAND","CF","SD","SD2","USB","USB2","USB3"
/* FF_STR_VOLUME_ID switches string support for volume ID.
/  When FF_STR_VOLUME_ID is set to 1, also pre-defined strings can be used as drive
/  number in the path name. FF_VOLUME_STRS defines the drive ID strings for each
/  logical drives. Number of items must be equal to FF_VOLUMES. Valid characters for
/  the drive ID strings are: A-Z and 0-9. */
/*FF_STR_VOLUME_ID切换了卷ID的字符串支持。
/当FF_STR_VOLUME_ID设置为1时，也可以使用预定义的字符串作为驱动器
/路径名中的数字。FF_VOLUME_STRS为每个文件定义驱动器ID字符串
/逻辑驱动器。项目的数量必须等于ff_volume。有效字符
/驱动器ID字符串是:A-Z和0-9。*/

#define FF_MULTI_PARTITION	0
/* This option switches support for multiple volumes on the physical drive.
/  By default (0), each logical drive number is bound to the same physical drive
/  number and only an FAT volume found on the physical drive will be mounted.
/  When this function is enabled (1), each logical drive number can be bound to
/  arbitrary physical drive and partition listed in the VolToPart[]. Also f_fdisk()
/  funciton will be available. */
/*0\xA3:单分区 1/2：多分*/

#define FF_MIN_SS		512
#define FF_MAX_SS		512
/* This set of options configures the range of sector size to be supported. (512,
/  1024, 2048 or 4096) Always set both 512 for most systems, generic memory card and
/  harddisk. But a larger value may be required for on-board flash memory and some
/  type of optical media. When FF_MAX_SS is larger than FF_MIN_SS, FatFs is configured
/  for variable sector size mode and disk_ioctl() function needs to implement
/  GET_SECTOR_SIZE command. */


#define FF_USE_TRIM		0
/* This option switches support for ATA-TRIM. (0:Disable or 1:Enable)
/  To enable Trim function, also CTRL_TRIM command should be implemented to the
/  disk_ioctl() function. */


#define FF_FS_NOFSINFO	0
/* If you need to know correct free space on the FAT32 volume, set bit 0 of this
/  option, and f_getfree() function at first time after volume mount will force
/  a full FAT scan. Bit 1 controls the use of last allocated cluster number.
/
/  bit0=0: Use free cluster count in the FSINFO if available.
/  bit0=1: Do not trust free cluster count in the FSINFO.
/  bit1=0: Use last allocated cluster number in the FSINFO if available.
/  bit1=1: Do not trust last allocated cluster number in the FSINFO.
*/



/*---------------------------------------------------------------------------/
/ System Configurations
/---------------------------------------------------------------------------*/

#define FF_FS_TINY		0		/* 0：正常 1：迷你的 0:Normal or 1:Tiny */
/* This option switches tiny buffer configuration. (0:Normal or 1:Tiny)
/  At the tiny configuration, size of file object (FIL) is shrinked FF_MAX_SS bytes.
/  Instead of private sector buffer eliminated from the file object, common sector
/  buffer in the filesystem object (FATFS) is used for the file data transfer. */
// 当FS_TINY为1，将减少内存的使用

#define FF_FS_EXFAT		0		//此选项切换对exFAT文件系统的支持。(0:禁用或1:启用)
/* This option switches support for exFAT filesystem. (0:Disable or 1:Enable)
/  When enable exFAT, also LFN needs to be enabled.
/  Note that enabling exFAT discards ANSI C (C89) compatibility. */

#define FF_FS_NORTC		0
#define FF_NORTC_MON	1
#define FF_NORTC_MDAY	1
#define FF_NORTC_YEAR	2017
/* The option FF_FS_NORTC switches timestamp functiton. If the system does not have
/  any RTC function or valid timestamp is not needed, set FF_FS_NORTC = 1 to disable
/  the timestamp function. All objects modified by FatFs will have a fixed timestamp
/  defined by FF_NORTC_MON, FF_NORTC_MDAY and FF_NORTC_YEAR in local time.
/  To enable timestamp function (FF_FS_NORTC = 0), get_fattime() function need to be
/  added to the project to read current time form real-time clock. FF_NORTC_MON,
/  FF_NORTC_MDAY and FF_NORTC_YEAR have no effect.
/  These options have no effect at read-only configuration (FF_FS_READONLY = 1). */


#define FF_FS_LOCK		0
/* The option FF_FS_LOCK switches file lock function to control duplicated file open
/  and illegal operation to open objects. This option must be 0 when FF_FS_READONLY
/  is 1.
/
/  0:  Disable file lock function. To avoid volume corruption, application program
/      should avoid illegal open, remove and rename to the open objects.
/  >0: Enable file lock function. The value defines how many files/sub-directories
/      can be opened simultaneously under file lock control. Note that the file
/      lock control is independent of re-entrancy. */
//0-->3 支持同时打开文件数 3个 

#define FF_FS_REENTRANT	0
#define FF_FS_TIMEOUT	1000
#define FF_SYNC_t		HANDLE
/* The option FF_FS_REENTRANT switches the re-entrancy (thread safe) of the FatFs
/  module itself. Note that regardless of this option, file access to different
/  volume is always re-entrant and volume control functions, f_mount(), f_mkfs()
/  and f_fdisk() function, are always not re-entrant. Only file/directory access
/  to the same volume is under control of this function.
/
/   0: Disable re-entrancy. FF_FS_TIMEOUT and FF_SYNC_t have no effect.
/   1: Enable re-entrancy. Also user provided synchronization handlers,
/      ff_req_grant(), ff_rel_grant(), ff_del_syncobj() and ff_cre_syncobj()
/      function, must be added to the project. Samples are available in
/      option/syscall.c.
/
/  The FF_FS_TIMEOUT defines timeout period in unit of time tick.
/  The FF_SYNC_t defines O/S dependent sync object type. e.g. HANDLE, ID, OS_EVENT*,
/  SemaphoreHandle_t and etc. A header file for O/S definitions needs to be
/  included somewhere in the scope of ff.h. */

/* #include <windows.h>	// O/S definitions  */



/*--- End of configuration options ---*/
