// simplewall
// Copyright (c) 2016, 2017 Henry++

#ifndef __MAIN_H__
#define __MAIN_H__

#include <windows.h>
#include <commctrl.h>
#include "resource.h"

// config
#define APP_NAME L"simplewall"
#define APP_NAME_SHORT L"simplewall"
#define APP_VERSION L"1.6"
#define APP_VERSION_RES 1,6
#define APP_COPYRIGHT L"(c) 2016, 2017 " _APP_AUTHOR L". All Rights Reserved."

#define WM_TRAYICON WM_APP + 1
#define UID 1984 // if you want to keep a secret, you must also hide it from yourself.

// guid
static const GUID GUID_SessionKey =
{0x1671cba0, 0x2d57, 0x4dbe, {0x8b, 0xfd, 0x33, 0xb5, 0xc8, 0xb9, 0x38, 0x38}};

static const GUID GUID_WfpProvider =
{0xb0d553e2, 0xc6a0, 0x4a9a, {0xae, 0xb8, 0xc7, 0x52, 0x48, 0x3e, 0xd6, 0x2f}};

static const GUID GUID_WfpSublayer =
{0x9fee6f59, 0xb951, 0x4f9a, {0xb5, 0x2f, 0x13, 0x3d, 0xcf, 0x7a, 0x42, 0x79}};

// deprecated and not used, but need for remove
static const GUID GUID_WfpOutboundCallout4 =
{0xf1251f1a, 0xab09, 0x4ce7, {0xba, 0xe3, 0x6c, 0xcc, 0xce, 0xf2, 0xc8, 0xca}};

static const GUID GUID_WfpOutboundCallout6 =
{0xfd497f2e, 0x46f5, 0x486d, {0xb0, 0xc, 0x3f, 0x7f, 0xe0, 0x7a, 0x94, 0xa6}};

static const GUID GUID_WfpInboundCallout4 =
{0xefc879ce, 0x3066, 0x45bb, {0x8a, 0x70, 0x17, 0xfe, 0x29, 0x78, 0x53, 0xc0}};

static const GUID GUID_WfpInboundCallout6 =
{0xd0420299, 0x52d8, 0x4f18, {0xbc, 0x80, 0x47, 0x3a, 0x24, 0x93, 0xf2, 0x69}};

static const GUID GUID_WfpListenCallout4 =
{0x51fa679d, 0x578b, 0x4835, {0xa6, 0x3e, 0xca, 0xd7, 0x68, 0x7f, 0x74, 0x95}};

static const GUID GUID_WfpListenCallout6 =
{0xa02187ca, 0xe655, 0x4adb, {0xa1, 0xf2, 0x47, 0xa2, 0xc9, 0x78, 0xf9, 0xce}};

// libs
#pragma comment(lib, "fwpuclnt.lib")
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ntdll.lib")
#pragma comment(lib, "version.lib")
#pragma comment(lib, "ws2_32.lib")

#define PROC_SYSTEM_PID 4
#define PROC_SYSTEM_NAME L"System"

#define PATH_LOG L"%userprofile%\\" APP_NAME_SHORT L".log"
#define PATH_LOG_ERROR L"%userprofile%\\" APP_NAME_SHORT L"_errors.log"

#define PATH_NTOSKRNL L"%systemroot%\\system32\\ntoskrnl.exe"
#define PATH_SVCHOST L"%systemroot%\\system32\\svchost.exe"

#define SECTION_BLOCKLIST L"blocklist_rules"
#define SECTION_SYSTEM L"system_rules"

#define TAB_SPACE L"   "
#define ERR_FORMAT L"%s() failed with error code 0x%.8lx (%s)"
#define RULE_DELIMETER L";"

// pugixml document configuration
#define PUGIXML_LOAD_FLAGS (pugi::parse_escapes)
#define PUGIXML_LOAD_ENCODING pugi::encoding_auto

#define PUGIXML_SAVE_FLAGS (pugi::format_indent | pugi::format_write_bom)
#define PUGIXML_SAVE_ENCODING pugi::encoding_wchar

// default colors
#define LISTVIEW_COLOR_CUSTOM RGB (255, 248, 202)
#define LISTVIEW_COLOR_INVALID RGB (255, 192, 203)
#define LISTVIEW_COLOR_NETWORK RGB (204, 187, 255)
#define LISTVIEW_COLOR_SILENT RGB (181, 181, 181)
#define LISTVIEW_COLOR_SYSTEM RGB(204, 255, 255)

// filter weights
#define FILTER_WEIGHT_HIGHEST 0xF
#define FILTER_WEIGHT_BLOCKLIST 0xE
#define FILTER_WEIGHT_CUSTOM 0xD
#define FILTER_WEIGHT_APPLICATION 0xC
#define FILTER_WEIGHT_LOWEST 0xB

EXTERN_C const IID IID_IImageList;

enum EnumDirection
{
	Out,
	In,
	Both,
};

enum EnumMode
{
	Whitelist,
	Blacklist,
	TrustNoOne,
};

struct STATIC_DATA
{
	SID* psid = nullptr;

	BOOL is_filtersinstalled = FALSE;
	BOOL is_firstapply = FALSE;
	BOOL is_popuperrors = FALSE;

	HIMAGELIST himg = nullptr;

	size_t def_icon_id = 0;
	HICON def_hicon = nullptr;

	HANDLE hengine = nullptr;
	HANDLE hevent = nullptr;
	HANDLE hlog = nullptr;

	HANDLE hthread = nullptr;
	HANDLE install_evt = nullptr;
	HANDLE destroy_evt = nullptr;
	HANDLE stop_evt = nullptr;

	WCHAR apps_path[MAX_PATH] = {0};
	WCHAR blocklist_path[MAX_PATH] = {0};
	WCHAR rules_custom_path[MAX_PATH] = {0};
	WCHAR rules_system_path[MAX_PATH] = {0};

	HWND hfind = nullptr;
	WCHAR search_string[128] = {0};

	WCHAR windows_dir[MAX_PATH] = {0};
	size_t wd_length = 0;

	size_t last_hash = 0;
	size_t my_hash = 0;
	size_t ntoskrnl_hash = 0;

	INT statusbar_height = 0;

	__time64_t errorlog_Last = 0;

	volatile LONG lock_access = 0;
	volatile LONG lock_apply = 0;
	volatile LONG lock_writelog = 0;
	volatile LONG lock_writestate = 0;
};

struct ITEM_APPLICATION
{
	size_t icon_id = 0;

	UINT error_count = 0;

	BOOL is_checked = FALSE;
	BOOL is_network = FALSE;
	BOOL is_system = FALSE;
	BOOL is_silent = FALSE;
	BOOL is_storeapp = FALSE; // win8 and above
	BOOL is_picoapp = FALSE; // win10 and above

	WCHAR file_name[64] = {0};
	WCHAR file_dir[MAX_PATH] = {0};

	WCHAR display_path[MAX_PATH] = {0};
	WCHAR real_path[MAX_PATH] = {0};

	WCHAR info[1024] = {0};
};

struct ITEM_RULE
{
	EnumDirection dir = Out;

	UINT8 protocol = 0;
	ADDRESS_FAMILY version = AF_UNSPEC;

	BOOL is_enabled = FALSE;
	BOOL is_block = FALSE;

	WCHAR name[128] = {0};
	WCHAR rule[1024] = {0};

	WCHAR apps[16384] = {0};
};

struct ITEM_LOG
{
	__time64_t timestamp = 0;

	size_t hash = 0;

	WCHAR protocol[16] = {0};
	WCHAR direction[16] = {0};

	WCHAR date[64] = {0};

	WCHAR domain[128] = {0};
	WCHAR username[128] = {0};

	WCHAR full_path[MAX_PATH] = {0};
	WCHAR address[MAX_PATH] = {0};

	WCHAR filter[MAX_PATH] = {0};
};

struct ITEM_PROCESS
{
	HBITMAP hbmp = nullptr;

	WCHAR display_path[64] = {0};
	WCHAR real_path[MAX_PATH] = {0};
};

struct ITEM_COLOR
{
	BOOL is_enabled = FALSE;

	UINT locale_id = 0;

	COLORREF default_clr;
	COLORREF clr;

	WCHAR locale_sid[64] = {0};
	WCHAR config[64] = {0};
	WCHAR config_color[64] = {0};
};

struct ITEM_PROTOCOL
{
	UINT8 v = 0;
	WCHAR t[32] = {0};
};

struct ITEM_ADDRESS
{
	ADDRESS_FAMILY af = 0;

	USHORT port = 0;

	UINT8 v6prefix = 0;
	UINT8 v6address[FWP_V6_ADDR_SIZE] = {0};

	UINT32 v4mask = 0;
	UINT32 v4address = 0;

	FWP_V4_ADDR_AND_MASK* ptr4 = nullptr;
	FWP_V6_ADDR_AND_MASK* ptr6 = nullptr;
};

// dropped events callback subscription (win7 and above)
typedef struct FWPM_NET_EVENT_HEADER3_
{
	FILETIME       timeStamp;
	UINT32         flags;
	FWP_IP_VERSION ipVersion;
	UINT8          ipProtocol;
	union
	{
		UINT32           localAddrV4;
		FWP_BYTE_ARRAY16 localAddrV6;
	};
	union
	{
		UINT32           remoteAddrV4;
		FWP_BYTE_ARRAY16 remoteAddrV6;
	};
	UINT16         localPort;
	UINT16         remotePort;
	UINT32         scopeId;
	FWP_BYTE_BLOB  appId;
	SID            *userId;
	FWP_AF         addressFamily;
	SID            *packageSid;
	wchar_t        *enterpriseId;
	UINT64         policyFlags;
	FWP_BYTE_BLOB  effectiveName;
} FWPM_NET_EVENT_HEADER3;

typedef struct FWPM_NET_EVENT3_
{
	FWPM_NET_EVENT_HEADER3 header;
	FWPM_NET_EVENT_TYPE    type;
	union
	{
		FWPM_NET_EVENT_IKEEXT_MM_FAILURE1 *ikeMmFailure;
		FWPM_NET_EVENT_IKEEXT_QM_FAILURE0 *ikeQmFailure;
		FWPM_NET_EVENT_IKEEXT_EM_FAILURE1 *ikeEmFailure;
		FWPM_NET_EVENT_CLASSIFY_DROP2     *classifyDrop;
		FWPM_NET_EVENT_IPSEC_KERNEL_DROP0 *ipsecDrop;
		FWPM_NET_EVENT_IPSEC_DOSP_DROP0   *idpDrop;
		FWPM_NET_EVENT_CLASSIFY_ALLOW0    *classifyAllow;
		FWPM_NET_EVENT_CAPABILITY_DROP0   *capabilityDrop;
		FWPM_NET_EVENT_CAPABILITY_ALLOW0  *capabilityAllow;
		FWPM_NET_EVENT_CLASSIFY_DROP_MAC0 *classifyDropMac;
	};
} FWPM_NET_EVENT3;

typedef void (CALLBACK *FWPM_NET_EVENT_CALLBACK2)(_Inout_ void* context, _In_ const FWPM_NET_EVENT3* event);

typedef DWORD (WINAPI *FWPMNES0) (HANDLE, const FWPM_NET_EVENT_SUBSCRIPTION0*, FWPM_NET_EVENT_CALLBACK0, LPVOID, HANDLE*);
typedef DWORD (WINAPI *FWPMNES1) (HANDLE, const FWPM_NET_EVENT_SUBSCRIPTION0*, FWPM_NET_EVENT_CALLBACK1, LPVOID, HANDLE*);
typedef DWORD (WINAPI *FWPMNES2) (HANDLE, const FWPM_NET_EVENT_SUBSCRIPTION0*, FWPM_NET_EVENT_CALLBACK2, LPVOID, HANDLE*);

typedef DWORD (WINAPI *FWPMNEU) (HANDLE, HANDLE);

// query process information
typedef struct _CLIENT_ID
{
	HANDLE UniqueProcess;
	HANDLE UniqueThread;
} CLIENT_ID, *PCLIENT_ID;

typedef struct _SYSTEM_THREAD_INFORMATION
{
	LARGE_INTEGER KernelTime;
	LARGE_INTEGER UserTime;
	LARGE_INTEGER CreateTime;
	ULONG WaitTime;
	PVOID StartAddress;
	CLIENT_ID ClientId;
	LONG Priority;
	LONG BasePriority;
	ULONG ContextSwitches;
	ULONG ThreadState;
	ULONG WaitReason;
} SYSTEM_THREAD_INFORMATION, *PSYSTEM_THREAD_INFORMATION;

typedef struct _SYSTEM_PROCESS_INFORMATION
{
	ULONG NextEntryOffset;
	ULONG NumberOfThreads;
	LARGE_INTEGER WorkingSetPrivateSize; // since VISTA
	ULONG HardFaultCount; // since WIN7
	ULONG NumberOfThreadsHighWatermark; // since WIN7
	ULONGLONG CycleTime; // since WIN7
	LARGE_INTEGER CreateTime;
	LARGE_INTEGER UserTime;
	LARGE_INTEGER KernelTime;
	UNICODE_STRING ImageName;
	LONG BasePriority;
	HANDLE UniqueProcessId;
	HANDLE InheritedFromUniqueProcessId;
	ULONG HandleCount;
	ULONG SessionId;
	ULONG_PTR UniqueProcessKey; // since VISTA (requires SystemExtendedProcessInformation)
	SIZE_T PeakVirtualSize;
	SIZE_T VirtualSize;
	ULONG PageFaultCount;
	SIZE_T PeakWorkingSetSize;
	SIZE_T WorkingSetSize;
	SIZE_T QuotaPeakPagedPoolUsage;
	SIZE_T QuotaPagedPoolUsage;
	SIZE_T QuotaPeakNonPagedPoolUsage;
	SIZE_T QuotaNonPagedPoolUsage;
	SIZE_T PagefileUsage;
	SIZE_T PeakPagefileUsage;
	SIZE_T PrivatePageCount;
	LARGE_INTEGER ReadOperationCount;
	LARGE_INTEGER WriteOperationCount;
	LARGE_INTEGER OtherOperationCount;
	LARGE_INTEGER ReadTransferCount;
	LARGE_INTEGER WriteTransferCount;
	LARGE_INTEGER OtherTransferCount;
	SYSTEM_THREAD_INFORMATION Threads[1];
} SYSTEM_PROCESS_INFORMATION, *PSYSTEM_PROCESS_INFORMATION;

struct OBJECT_NAME_INFORMATION
{
	UNICODE_STRING Name; // defined in winternl.h
	WCHAR NameBuffer;
};

#define SystemProcessInformation 5
#define ObjectNameInformation 1

extern "C" {
	NTSYSCALLAPI
		NTSTATUS
		NTAPI
		NtQuerySystemInformation (
		_In_ UINT SystemInformationClass,
		_Out_writes_bytes_opt_ (SystemInformationLength) PVOID SystemInformation,
		_In_ ULONG SystemInformationLength,
		_Out_opt_ PULONG ReturnLength
		);

	NTSYSCALLAPI
		NTSTATUS
		NTAPI
		NtQueryObject (
		_In_ HANDLE Handle,
		_In_ UINT ObjectInformationClass,
		_Out_writes_bytes_opt_ (ObjectInformationLength) PVOID ObjectInformation,
		_In_ ULONG ObjectInformationLength,
		_Out_opt_ PULONG ReturnLength
		);
}

#endif // __MAIN_H__
