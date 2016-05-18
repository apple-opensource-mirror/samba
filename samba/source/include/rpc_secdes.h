/* 
   Unix SMB/CIFS implementation.
   SMB parameters and setup
   Copyright (C) Andrew Tridgell              1992-2000
   Copyright (C) Luke Kenneth Casson Leighton 1996-2000
   
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#ifndef _RPC_SECDES_H /* _RPC_SECDES_H */
#define _RPC_SECDES_H 

#define SEC_RIGHTS_QUERY_VALUE		0x00000001
#define SEC_RIGHTS_SET_VALUE		0x00000002
#define SEC_RIGHTS_CREATE_SUBKEY	0x00000004
#define SEC_RIGHTS_ENUM_SUBKEYS		0x00000008
#define SEC_RIGHTS_NOTIFY		0x00000010
#define SEC_RIGHTS_CREATE_LINK		0x00000020
#define SEC_RIGHTS_READ			0x00020019
#define SEC_RIGHTS_FULL_CONTROL		0x000f003f
#define SEC_RIGHTS_MAXIMUM_ALLOWED	0x02000000

/* for ADS */
#define	SEC_RIGHTS_LIST_CONTENTS	0x4
#define SEC_RIGHTS_LIST_OBJECT		0x80
#define	SEC_RIGHTS_READ_ALL_PROP	0x10
#define	SEC_RIGHTS_READ_PERMS		0x20000
#define SEC_RIGHTS_WRITE_ALL_VALID	0x8
#define	SEC_RIGHTS_WRITE_ALL_PROP	0x20     
#define SEC_RIGHTS_MODIFY_OWNER		0x80000
#define	SEC_RIGHTS_MODIFY_PERMS		0x40000
#define	SEC_RIGHTS_CREATE_CHILD		0x1
#define	SEC_RIGHTS_DELETE_CHILD		0x2
#define SEC_RIGHTS_DELETE_SUBTREE	0x40
#define SEC_RIGHTS_DELETE               0x10000 /* advanced/special/object/delete */
#define SEC_RIGHTS_EXTENDED		0x100 /* change/reset password, receive/send as*/
#define	SEC_RIGHTS_CHANGE_PASSWD	SEC_RIGHTS_EXTENDED
#define	SEC_RIGHTS_RESET_PASSWD		SEC_RIGHTS_EXTENDED
#define SEC_RIGHTS_FULL_CTRL		0xf01ff

#define SEC_ACE_OBJECT_PRESENT           0x00000001 /* thanks for Jim McDonough <jmcd@us.ibm.com> */
#define SEC_ACE_OBJECT_INHERITED_PRESENT 0x00000002

#define SEC_ACE_FLAG_OBJECT_INHERIT		0x1
#define SEC_ACE_FLAG_CONTAINER_INHERIT		0x2
#define SEC_ACE_FLAG_NO_PROPAGATE_INHERIT	0x4
#define SEC_ACE_FLAG_INHERIT_ONLY		0x8
#define SEC_ACE_FLAG_INHERITED_ACE		0x10 /* New for Windows 2000 */
#define SEC_ACE_FLAG_VALID_INHERIT		0xf
#define SEC_ACE_FLAG_SUCCESSFUL_ACCESS		0x40
#define SEC_ACE_FLAG_FAILED_ACCESS		0x80

#define SEC_ACE_TYPE_ACCESS_ALLOWED		0x0
#define SEC_ACE_TYPE_ACCESS_DENIED		0x1
#define SEC_ACE_TYPE_SYSTEM_AUDIT		0x2
#define SEC_ACE_TYPE_SYSTEM_ALARM		0x3
#define SEC_ACE_TYPE_ALLOWED_COMPOUND		0x4
#define SEC_ACE_TYPE_ACCESS_ALLOWED_OBJECT	0x5
#define SEC_ACE_TYPE_ACCESS_DENIED_OBJECT     	0x6
#define SEC_ACE_TYPE_SYSTEM_AUDIT_OBJECT      	0x7
#define SEC_ACE_TYPE_SYSTEM_ALARM_OBJECT	0x8

#define SEC_DESC_OWNER_DEFAULTED	0x0001
#define SEC_DESC_GROUP_DEFAULTED	0x0002
#define SEC_DESC_DACL_PRESENT		0x0004
#define SEC_DESC_DACL_DEFAULTED		0x0008
#define SEC_DESC_SACL_PRESENT		0x0010
#define SEC_DESC_SACL_DEFAULTED		0x0020
#define SEC_DESC_DACL_TRUSTED		0x0040
#define SEC_DESC_SERVER_SECURITY	0x0080
/*
 * New Windows 2000 bits.
 */
#define SE_DESC_DACL_AUTO_INHERIT_REQ	0x0100
#define SE_DESC_SACL_AUTO_INHERIT_REQ	0x0200
#define SE_DESC_DACL_AUTO_INHERITED	0x0400
#define SE_DESC_SACL_AUTO_INHERITED	0x0800
#define SE_DESC_DACL_PROTECTED		0x1000
#define SE_DESC_SACL_PROTECTED		0x2000

/* Don't know what this means. */
#define SEC_DESC_RM_CONTROL_VALID	0x4000

#define SEC_DESC_SELF_RELATIVE		0x8000

/* security information */
#define OWNER_SECURITY_INFORMATION	0x00000001
#define GROUP_SECURITY_INFORMATION	0x00000002
#define DACL_SECURITY_INFORMATION	0x00000004
#define SACL_SECURITY_INFORMATION	0x00000008
/* Extra W2K flags. */
#define UNPROTECTED_SACL_SECURITY_INFORMATION	0x10000000
#define UNPROTECTED_DACL_SECURITY_INFORMATION	0x20000000
#define PROTECTED_SACL_SECURITY_INFORMATION	0x40000000
#define PROTECTED_DACL_SECURITY_INFORMATION	0x80000000

#define ALL_SECURITY_INFORMATION (OWNER_SECURITY_INFORMATION|GROUP_SECURITY_INFORMATION|\
					DACL_SECURITY_INFORMATION|SACL_SECURITY_INFORMATION|\
					UNPROTECTED_SACL_SECURITY_INFORMATION|\
					UNPROTECTED_DACL_SECURITY_INFORMATION|\
					PROTECTED_SACL_SECURITY_INFORMATION|\
					PROTECTED_DACL_SECURITY_INFORMATION)

/* SEC_ACCESS */
typedef struct security_info_info
{
	uint32 mask;

} SEC_ACCESS;

/* SEC_ACE */
typedef struct security_ace_info
{
	uint8 type;  /* xxxx_xxxx_ACE_TYPE - e.g allowed / denied etc */
	uint8 flags; /* xxxx_INHERIT_xxxx - e.g OBJECT_INHERIT_ACE */
	uint16 size;

	SEC_ACCESS info;

	/* this stuff may be present when type is XXXX_TYPE_XXXX_OBJECT */
	uint32  obj_flags; /* xxxx_ACE_OBJECT_xxxx e.g present/inherited present etc */
	struct uuid obj_guid;  /* object GUID */
	struct uuid inh_guid;  /* inherited object GUID */		
        /* eof object stuff */

	DOM_SID trustee;

} SEC_ACE;
#define  SEC_ACE_HEADER_SIZE (2 * sizeof(uint8) + sizeof(uint16) + sizeof(uint32))

#ifndef ACL_REVISION
#define ACL_REVISION 0x3
#endif

#ifndef NT4_ACL_REVISION
#define NT4_ACL_REVISION 0x2
#endif

#ifndef _SEC_ACL
/* SEC_ACL */
typedef struct security_acl_info
{
	uint16 revision; /* 0x0003 */
	uint16 size; /* size in bytes of the entire ACL structure */
	uint32 num_aces; /* number of Access Control Entries */

	SEC_ACE *ace;

} SEC_ACL;
#define  SEC_ACL_HEADER_SIZE (2 * sizeof(uint16) + sizeof(uint32))
#define _SEC_ACL
#endif

#ifndef SEC_DESC_REVISION
#define SEC_DESC_REVISION 0x1
#endif

#ifndef _SEC_DESC
/* SEC_DESC */
typedef struct security_descriptor_info
{
	uint16 revision; /* 0x0001 */
	uint16 type;     /* SEC_DESC_xxxx flags */

	uint32 off_owner_sid; /* offset to owner sid */
	uint32 off_grp_sid  ; /* offset to group sid */
	uint32 off_sacl     ; /* offset to system list of permissions */
	uint32 off_dacl     ; /* offset to list of permissions */

	SEC_ACL *dacl; /* user ACL */
	SEC_ACL *sacl; /* system ACL */
	DOM_SID *owner_sid; 
	DOM_SID *grp_sid;

} SEC_DESC;
#define  SEC_DESC_HEADER_SIZE (2 * sizeof(uint16) + 4 * sizeof(uint32))
#define _SEC_DESC
#endif

#ifndef _SEC_DESC_BUF
/* SEC_DESC_BUF */
typedef struct sec_desc_buf_info
{
	uint32 max_len;
	uint32 ptr;
	uint32 len;

	SEC_DESC *sec;

} SEC_DESC_BUF;
#define _SEC_DESC_BUF
#endif

/* A type to describe the mapping of generic access rights to object
   specific access rights. */

typedef struct generic_mapping {
	uint32 generic_read;
	uint32 generic_write;
	uint32 generic_execute;
	uint32 generic_all;
} GENERIC_MAPPING;

typedef struct standard_mapping {
	uint32 std_read;
	uint32 std_write;
	uint32 std_execute;
	uint32 std_all;
} STANDARD_MAPPING;


/* Security Access Masks Rights */

#define SPECIFIC_RIGHTS_MASK	0x0000FFFF
#define STANDARD_RIGHTS_MASK	0x00FF0000
#define GENERIC_RIGHTS_MASK	0xF0000000

#define SEC_RIGHT_SYSTEM_SECURITY	0x01000000
#define SEC_RIGHT_MAXIMUM_ALLOWED	0x02000000

/* Generic access rights */

#define GENERIC_RIGHT_ALL_ACCESS	0x10000000
#define GENERIC_RIGHT_EXECUTE_ACCESS	0x20000000
#define GENERIC_RIGHT_WRITE_ACCESS	0x40000000
#define GENERIC_RIGHT_READ_ACCESS	0x80000000

/* Standard access rights. */

#define STD_RIGHT_DELETE_ACCESS		0x00010000
#define STD_RIGHT_READ_CONTROL_ACCESS	0x00020000
#define STD_RIGHT_WRITE_DAC_ACCESS	0x00040000
#define STD_RIGHT_WRITE_OWNER_ACCESS	0x00080000
#define STD_RIGHT_SYNCHRONIZE_ACCESS	0x00100000

#define STD_RIGHT_ALL_ACCESS		0x001F0000

/* Combinations of standard masks. */
#define STANDARD_RIGHTS_ALL_ACCESS	STD_RIGHT_ALL_ACCESS /* 0x001f0000 */
#define STANDARD_RIGHTS_EXECUTE_ACCESS	STD_RIGHT_READ_CONTROL_ACCESS /* 0x00020000 */
#define STANDARD_RIGHTS_READ_ACCESS	STD_RIGHT_READ_CONTROL_ACCESS /* 0x00020000 */
#define STANDARD_RIGHTS_WRITE_ACCESS	STD_RIGHT_READ_CONTROL_ACCESS /* 0x00020000 */
#define STANDARD_RIGHTS_REQUIRED_ACCESS \
		(STD_RIGHT_DELETE_ACCESS	| \
		STD_RIGHT_READ_CONTROL_ACCESS	| \
		STD_RIGHT_WRITE_DAC_ACCESS	| \
		STD_RIGHT_WRITE_OWNER_ACCESS)	/* 0x000f0000 */

/* File Object specific access rights */

#define SA_RIGHT_FILE_READ_DATA		0x00000001
#define SA_RIGHT_FILE_WRITE_DATA	0x00000002
#define SA_RIGHT_FILE_APPEND_DATA	0x00000004
#define SA_RIGHT_FILE_READ_EA		0x00000008
#define SA_RIGHT_FILE_WRITE_EA		0x00000010
#define SA_RIGHT_FILE_EXECUTE		0x00000020
#define SA_RIGHT_FILE_DELETE_CHILD	0x00000040
#define SA_RIGHT_FILE_READ_ATTRIBUTES	0x00000080
#define SA_RIGHT_FILE_WRITE_ATTRIBUTES	0x00000100

#define SA_RIGHT_FILE_ALL_ACCESS	0x000001FF

#define GENERIC_RIGHTS_FILE_ALL_ACCESS \
		(STANDARD_RIGHTS_REQUIRED_ACCESS| \
		STD_RIGHT_SYNCHRONIZE_ACCESS	| \
		SA_RIGHT_FILE_ALL_ACCESS)

#define GENERIC_RIGHTS_FILE_READ	\
		(STANDARD_RIGHTS_READ_ACCESS	| \
		STD_RIGHT_SYNCHRONIZE_ACCESS	| \
		SA_RIGHT_FILE_READ_DATA		| \
		SA_RIGHT_FILE_READ_ATTRIBUTES	| \
		SA_RIGHT_FILE_READ_EA)

#define GENERIC_RIGHTS_FILE_WRITE \
		(STANDARD_RIGHTS_WRITE_ACCESS	| \
		STD_RIGHT_SYNCHRONIZE_ACCESS	| \
		SA_RIGHT_FILE_WRITE_DATA	| \
		SA_RIGHT_FILE_WRITE_ATTRIBUTES	| \
		SA_RIGHT_FILE_WRITE_EA		| \
		SA_RIGHT_FILE_APPEND_DATA)

#define GENERIC_RIGHTS_FILE_EXECUTE \
		(STANDARD_RIGHTS_EXECUTE_ACCESS	| \
		SA_RIGHT_FILE_READ_ATTRIBUTES	| \
		SA_RIGHT_FILE_EXECUTE)            

		
/* SAM server specific access rights */

#define SA_RIGHT_SAM_CONNECT_SERVER	0x00000001
#define SA_RIGHT_SAM_SHUTDOWN_SERVER	0x00000002
#define SA_RIGHT_SAM_INITIALISE_SERVER	0x00000004
#define SA_RIGHT_SAM_CREATE_DOMAIN	0x00000008
#define SA_RIGHT_SAM_ENUM_DOMAINS	0x00000010
#define SA_RIGHT_SAM_OPEN_DOMAIN	0x00000020

#define SA_RIGHT_SAM_ALL_ACCESS		0x0000003F

#define GENERIC_RIGHTS_SAM_ALL_ACCESS \
		(STANDARD_RIGHTS_REQUIRED_ACCESS| \
		SA_RIGHT_SAM_ALL_ACCESS)

#define GENERIC_RIGHTS_SAM_READ	\
		(STANDARD_RIGHTS_READ_ACCESS	| \
		SA_RIGHT_SAM_ENUM_DOMAINS)

#define GENERIC_RIGHTS_SAM_WRITE \
		(STANDARD_RIGHTS_WRITE_ACCESS	| \
		SA_RIGHT_SAM_CREATE_DOMAIN	| \
		SA_RIGHT_SAM_INITIALISE_SERVER	| \
		SA_RIGHT_SAM_SHUTDOWN_SERVER)

#define GENERIC_RIGHTS_SAM_EXECUTE \
		(STANDARD_RIGHTS_EXECUTE_ACCESS	| \
		SA_RIGHT_SAM_OPEN_DOMAIN	| \
		SA_RIGHT_SAM_CONNECT_SERVER)            


/* Domain Object specific access rights */

#define SA_RIGHT_DOMAIN_LOOKUP_INFO_1		0x00000001
#define SA_RIGHT_DOMAIN_SET_INFO_1		0x00000002
#define SA_RIGHT_DOMAIN_LOOKUP_INFO_2		0x00000004
#define SA_RIGHT_DOMAIN_SET_INFO_2		0x00000008
#define SA_RIGHT_DOMAIN_CREATE_USER		0x00000010
#define SA_RIGHT_DOMAIN_CREATE_GROUP		0x00000020
#define SA_RIGHT_DOMAIN_CREATE_ALIAS		0x00000040
#define SA_RIGHT_DOMAIN_LOOKUP_ALIAS_BY_MEM	0x00000080
#define SA_RIGHT_DOMAIN_ENUM_ACCOUNTS		0x00000100
#define SA_RIGHT_DOMAIN_OPEN_ACCOUNT		0x00000200
#define SA_RIGHT_DOMAIN_SET_INFO_3		0x00000400

#define SA_RIGHT_DOMAIN_ALL_ACCESS		0x000007FF

#define GENERIC_RIGHTS_DOMAIN_ALL_ACCESS \
		(STANDARD_RIGHTS_REQUIRED_ACCESS| \
		SA_RIGHT_DOMAIN_ALL_ACCESS)

#define GENERIC_RIGHTS_DOMAIN_READ \
		(STANDARD_RIGHTS_READ_ACCESS		| \
		SA_RIGHT_DOMAIN_LOOKUP_ALIAS_BY_MEM	| \
		SA_RIGHT_DOMAIN_LOOKUP_INFO_2)

#define GENERIC_RIGHTS_DOMAIN_WRITE \
		(STANDARD_RIGHTS_WRITE_ACCESS	| \
		SA_RIGHT_DOMAIN_SET_INFO_3	| \
		SA_RIGHT_DOMAIN_CREATE_ALIAS	| \
		SA_RIGHT_DOMAIN_CREATE_GROUP	| \
		SA_RIGHT_DOMAIN_CREATE_USER	| \
		SA_RIGHT_DOMAIN_SET_INFO_2	| \
		SA_RIGHT_DOMAIN_SET_INFO_1)

#define GENERIC_RIGHTS_DOMAIN_EXECUTE \
		(STANDARD_RIGHTS_EXECUTE_ACCESS	| \
		SA_RIGHT_DOMAIN_OPEN_ACCOUNT	| \
		SA_RIGHT_DOMAIN_ENUM_ACCOUNTS	| \
		SA_RIGHT_DOMAIN_LOOKUP_INFO_1)            


/* User Object specific access rights */

#define SA_RIGHT_USER_GET_NAME_ETC	0x00000001
#define SA_RIGHT_USER_GET_LOCALE	0x00000002
#define SA_RIGHT_USER_SET_LOC_COM	0x00000004
#define SA_RIGHT_USER_GET_LOGONINFO	0x00000008
#define SA_RIGHT_USER_ACCT_FLAGS_EXPIRY	0x00000010
#define SA_RIGHT_USER_SET_ATTRIBUTES	0x00000020
#define SA_RIGHT_USER_CHANGE_PASSWORD	0x00000040
#define SA_RIGHT_USER_SET_PASSWORD	0x00000080
#define SA_RIGHT_USER_GET_GROUPS	0x00000100
#define SA_RIGHT_USER_READ_GROUP_MEM	0x00000200
#define SA_RIGHT_USER_CHANGE_GROUP_MEM	0x00000400

#define SA_RIGHT_USER_ALL_ACCESS	0x000007FF

#define GENERIC_RIGHTS_USER_ALL_ACCESS \
		(STANDARD_RIGHTS_REQUIRED_ACCESS| \
		SA_RIGHT_USER_ALL_ACCESS)	/* 0x000f07ff */

#define GENERIC_RIGHTS_USER_READ \
		(STANDARD_RIGHTS_READ_ACCESS	| \
		SA_RIGHT_USER_READ_GROUP_MEM	| \
		SA_RIGHT_USER_GET_GROUPS	| \
		SA_RIGHT_USER_ACCT_FLAGS_EXPIRY	| \
		SA_RIGHT_USER_GET_LOGONINFO	| \
		SA_RIGHT_USER_GET_LOCALE)	/* 0x0002031a */

#define GENERIC_RIGHTS_USER_WRITE \
		(STANDARD_RIGHTS_WRITE_ACCESS	| \
		SA_RIGHT_USER_CHANGE_PASSWORD	| \
		SA_RIGHT_USER_SET_LOC_COM)	/* 0x00020044 */

#define GENERIC_RIGHTS_USER_EXECUTE \
		(STANDARD_RIGHTS_EXECUTE_ACCESS	| \
		SA_RIGHT_USER_CHANGE_PASSWORD	| \
		SA_RIGHT_USER_GET_NAME_ETC )	/* 0x00020041 */


/* Group Object specific access rights */

#define SA_RIGHT_GROUP_LOOKUP_INFO	0x00000001
#define SA_RIGHT_GROUP_SET_INFO		0x00000002
#define SA_RIGHT_GROUP_ADD_MEMBER	0x00000004
#define SA_RIGHT_GROUP_REMOVE_MEMBER	0x00000008
#define SA_RIGHT_GROUP_GET_MEMBERS	0x00000010

#define SA_RIGHT_GROUP_ALL_ACCESS	0x0000001F

#define GENERIC_RIGHTS_GROUP_ALL_ACCESS \
		(STANDARD_RIGHTS_REQUIRED_ACCESS| \
		SA_RIGHT_GROUP_ALL_ACCESS)	/* 0x000f001f */

#define GENERIC_RIGHTS_GROUP_READ \
		(STANDARD_RIGHTS_READ_ACCESS	| \
		SA_RIGHT_GROUP_GET_MEMBERS)	/* 0x00020010 */

#define GENERIC_RIGHTS_GROUP_WRITE \
		(STANDARD_RIGHTS_WRITE_ACCESS	| \
		SA_RIGHT_GROUP_REMOVE_MEMBER	| \
		SA_RIGHT_GROUP_ADD_MEMBER	| \
		SA_RIGHT_GROUP_SET_INFO )	/* 0x0002000e */

#define GENERIC_RIGHTS_GROUP_EXECUTE \
		(STANDARD_RIGHTS_EXECUTE_ACCESS	| \
		SA_RIGHT_GROUP_LOOKUP_INFO)	/* 0x00020001 */


/* Alias Object specific access rights */

#define SA_RIGHT_ALIAS_ADD_MEMBER	0x00000001
#define SA_RIGHT_ALIAS_REMOVE_MEMBER	0x00000002
#define SA_RIGHT_ALIAS_GET_MEMBERS	0x00000004
#define SA_RIGHT_ALIAS_LOOKUP_INFO	0x00000008
#define SA_RIGHT_ALIAS_SET_INFO		0x00000010

#define SA_RIGHT_ALIAS_ALL_ACCESS 	0x0000001F

#define GENERIC_RIGHTS_ALIAS_ALL_ACCESS \
		(STANDARD_RIGHTS_REQUIRED_ACCESS| \
		SA_RIGHT_ALIAS_ALL_ACCESS)	/* 0x000f001f */

#define GENERIC_RIGHTS_ALIAS_READ \
		(STANDARD_RIGHTS_READ_ACCESS	| \
		SA_RIGHT_ALIAS_GET_MEMBERS )	/* 0x00020004 */

#define GENERIC_RIGHTS_ALIAS_WRITE \
		(STANDARD_RIGHTS_WRITE_ACCESS	| \
		SA_RIGHT_ALIAS_REMOVE_MEMBER	| \
		SA_RIGHT_ALIAS_ADD_MEMBER	| \
		SA_RIGHT_ALIAS_SET_INFO )	/* 0x00020013 */

#define GENERIC_RIGHTS_ALIAS_EXECUTE \
		(STANDARD_RIGHTS_EXECUTE_ACCESS	| \
		SA_RIGHT_ALIAS_LOOKUP_INFO )	/* 0x00020008 */

#endif /* _RPC_SECDES_H */
