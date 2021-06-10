/* SCHEMA PRODUCED DATE - TIME : 6/10/2021 - 11:43:01 */
#pragma section lightwave_rp_code_enum
/* Definition LIGHTWAVE-RP-CODE-ENUM created on 06/10/2021 at 11:43 */
enum
{
   lw_rp_success = 0,
   lw_rp_info = 1,
   lw_rp_error = 2
};
typedef short                           lightwave_rp_code_enum_def;
#pragma section lightwave_info_code_enum
/* Definition LIGHTWAVE-INFO-CODE-ENUM created on 06/10/2021 at 11:43 */
enum
{
   lw_info_field_truncated = 100,
   lw_info_array_truncated = 101
};
typedef short                           lightwave_info_code_enum_def;
#pragma section lightwave_error_src_enum
/* Definition LIGHTWAVE-ERROR-SRC-ENUM created on 06/10/2021 at 11:43 */
enum
{
   lw_error_src_lightwave = 1,
   lw_error_src_http = 2,
   lw_error_src_tcpip = 3,
   lw_error_src_ssl = 4
};
typedef short                           lightwave_error_src_enum_def;
#pragma section lightwave_error_enum
/* Definition LIGHTWAVE-ERROR-ENUM created on 06/10/2021 at 11:43 */
enum
{
   lw_error_invalid_license = 1,
   lw_error_invalid_header = 2,
   lw_error_invalid_rq_code = 3,
   lw_error_invalid_type = 4,
   lw_error_serialization_error = 5,
   lw_error_deserialization_error = 6,
   lw_error_request_timeout = 7,
   lw_error_response_not_defined = 12,
   lw_error_invalid_uri_scheme = 100,
   lw_error_invalid_api_def = 101,
   lw_error_invalid_base_uri = 102,
   lw_error_invalid_hdr_version = 103,
   lw_error_signature_error = 104,
   lw_error_internal_error = 500
};
typedef short                           lightwave_error_enum_def;
#pragma section lightwave_rq_header
/* Definition LIGHTWAVE-RQ-HEADER created on 06/10/2021 at 11:43 */
#include <tnsint.h>
#pragma fieldalign shared2 __lightwave_rq_header
typedef struct __lightwave_rq_header
{
   short                           rq_code;
   unsigned short                  rq_version;
   __uint32_t                      rq_timeout;
   char                            reserved[24];
} lightwave_rq_header_def;
#define lightwave_rq_header_def_Size 32
#pragma section lightwave_rp_header
/* Definition LIGHTWAVE-RP-HEADER created on 06/10/2021 at 11:43 */
#pragma fieldalign shared2 __lightwave_rp_header
typedef struct __lightwave_rp_header
{
   short                           rp_code;
   short                           http_status;
   short                           info_code;
   short                           info_detail;
   char                            reserved[24];
} lightwave_rp_header_def;
#define lightwave_rp_header_def_Size 32
#pragma section lightwave_error_rp
/* Definition LIGHTWAVE-ERROR-RP created on 06/10/2021 at 11:43 */
#include <tnsint.h>
#pragma fieldalign shared2 __lightwave_error_rp
typedef struct __lightwave_error_rp
{
   lightwave_rp_header_def         lightwave_rp_header;
   __int32_t                       error_source;
   __int32_t                       error_code;
   __int32_t                       error_subcode;
   char                            error_message[4096];
} lightwave_error_rp_def;
#define lightwave_error_rp_def_Size 4140
#pragma section sample_lwc_cybersource_val
/* Definition SAMPLE-LWC-CYBERSOURCE-VAL created on 06/10/2021 at 11:43 */
#pragma fieldalign shared2 __sample_lwc_cybersource_val
typedef struct __sample_lwc_cybersource_val
{
   short                           rq_ics_transaction;
   /*value is 1*/
} sample_lwc_cybersource_val_def;
#define sample_lwc_cybersource_val_def_Size 2
#pragma section sample_lwc_cybersource_enm
/* Definition SAMPLE-LWC-CYBERSOURCE-ENM created on 06/10/2021 at 11:43 */
enum
{
   rq_ics_transaction = 1
};
typedef short                           sample_lwc_cybersource_enm_def;
#pragma section username_token_type
/* Definition USERNAME-TOKEN-TYPE created on 06/10/2021 at 11:43 */
#pragma fieldalign shared2 __username_token_type
typedef struct __username_token_type
{
   char                            username[32];
   char                            password[512];
   char                            type_rw[128];
} username_token_type_def;
#define username_token_type_def_Size 672
#pragma section security_type
/* Definition SECURITY-TYPE created on 06/10/2021 at 11:43 */
#pragma fieldalign shared2 __security_type
typedef struct __security_type
{
   username_token_type_def         username_token;
   char                            must_understand[32];
} security_type_def;
#define security_type_def_Size 704
#pragma section header_type
/* Definition HEADER-TYPE created on 06/10/2021 at 11:43 */
#pragma fieldalign shared2 __header_type
typedef struct __header_type
{
   security_type_def               security_rw;
   char                            must_understand[32];
} header_type_def;
#define header_type_def_Size 736
#pragma section bill_to_type
/* Definition BILL-TO-TYPE created on 06/10/2021 at 11:43 */
#pragma fieldalign shared2 __bill_to_type
typedef struct __bill_to_type
{
   char                            first_name[32];
   char                            last_name[32];
   char                            street_1[32];
   char                            city[32];
   char                            state[32];
   char                            postal_code[32];
   char                            country[32];
   char                            email[32];
} bill_to_type_def;
#define bill_to_type_def_Size 256
#pragma section item_type
/* Definition ITEM-TYPE created on 06/10/2021 at 11:43 */
#include <tnsint.h>
#pragma fieldalign shared2 __item_type
typedef struct __item_type
{
   char                            unit_price[32];
   __int32_t                       quantity;
   char                            id[32];
} item_type_def;
#define item_type_def_Size 68
#pragma section purchase_totals_type
/* Definition PURCHASE-TOTALS-TYPE created on 06/10/2021 at 11:43 */
#pragma fieldalign shared2 __purchase_totals_type
typedef struct __purchase_totals_type
{
   char                            currency_rw[32];
} purchase_totals_type_def;
#define purchase_totals_type_def_Size 32
#pragma section card_type
/* Definition CARD-TYPE created on 06/10/2021 at 11:43 */
#pragma fieldalign shared2 __card_type
typedef struct __card_type
{
   char                            account_number[32];
   char                            expiration_month[8];
   char                            expiration_year[8];
} card_type_def;
#define card_type_def_Size 48
#pragma section cc_auth_service_type
/* Definition CC-AUTH-SERVICE-TYPE created on 06/10/2021 at 11:43 */
#pragma fieldalign shared2 __cc_auth_service_type
typedef struct __cc_auth_service_type
{
   char                            run_rw[16];
} cc_auth_service_type_def;
#define cc_auth_service_type_def_Size 16
#pragma section request_message_type
/* Definition REQUEST-MESSAGE-TYPE created on 06/10/2021 at 11:43 */
#pragma fieldalign shared2 __request_message_type
typedef struct __request_message_type
{
   char                            merchant_id[32];
   char                            merchant_reference_code[32];
   bill_to_type_def                bill_to;
   __int32_t                       item_count;
   item_type_def                   item[10];
   purchase_totals_type_def        purchase_totals;
   card_type_def                   card;
   cc_auth_service_type_def        cc_auth_service;
} request_message_type_def;
#define request_message_type_def_Size 1100
#pragma section body_type
/* Definition BODY-TYPE created on 06/10/2021 at 11:43 */
#pragma fieldalign shared2 __body_type
typedef struct __body_type
{
   request_message_type_def        request_message;
} body_type_def;
#define body_type_def_Size 1100
#pragma section request_message_soap
/* Definition REQUEST-MESSAGE-SOAP created on 06/10/2021 at 11:43 */
#pragma fieldalign shared2 __request_message_soap
typedef struct __request_message_soap
{
   header_type_def                 header;
   body_type_def                   body;
} request_message_soap_def;
#define request_message_soap_def_Size 1836
#pragma section timestamp_type
/* Definition TIMESTAMP-TYPE created on 06/10/2021 at 11:43 */
#pragma fieldalign shared2 __timestamp_type
typedef struct __timestamp_type
{
   long long                       created;
   char                            id[32];
} timestamp_type_def;
#define timestamp_type_def_Size 40
#pragma section security_type_01
/* Definition SECURITY-TYPE-01 created on 06/10/2021 at 11:43 */
#pragma fieldalign shared2 __security_type_01
typedef struct __security_type_01
{
   timestamp_type_def              timestamp;
   char                            id[32];
} security_type_01_def;
#define security_type_01_def_Size 72
#pragma section header_type_01
/* Definition HEADER-TYPE-01 created on 06/10/2021 at 11:43 */
#pragma fieldalign shared2 __header_type_01
typedef struct __header_type_01
{
   security_type_01_def            security_rw;
} header_type_01_def;
#define header_type_01_def_Size 72
#pragma section cc_auth_reply_type
/* Definition CC-AUTH-REPLY-TYPE created on 06/10/2021 at 11:43 */
#include <tnsint.h>
#pragma fieldalign shared2 __cc_auth_reply_type
typedef struct __cc_auth_reply_type
{
   __int32_t                       reason_code;
} cc_auth_reply_type_def;
#define cc_auth_reply_type_def_Size 4
#pragma section reply_message_type
/* Definition REPLY-MESSAGE-TYPE created on 06/10/2021 at 11:43 */
#pragma fieldalign shared2 __reply_message_type
typedef struct __reply_message_type
{
   char                            merchant_reference_code[32];
   char                            request_id[64];
   char                            decision[32];
   __int32_t                       reason_code;
   char                            invalid_field[32];
   char                            request_token[80];
   cc_auth_reply_type_def          cc_auth_reply;
} reply_message_type_def;
#define reply_message_type_def_Size 248
#pragma section body_type_01
/* Definition BODY-TYPE-01 created on 06/10/2021 at 11:43 */
#pragma fieldalign shared2 __body_type_01
typedef struct __body_type_01
{
   reply_message_type_def          reply_message;
} body_type_01_def;
#define body_type_01_def_Size 248
#pragma section reply_message_soap
/* Definition REPLY-MESSAGE-SOAP created on 06/10/2021 at 11:43 */
#pragma fieldalign shared2 __reply_message_soap
typedef struct __reply_message_soap
{
   header_type_01_def              header;
   body_type_01_def                body;
} reply_message_soap_def;
#define reply_message_soap_def_Size 320
#pragma section fault_type
/* Definition FAULT-TYPE created on 06/10/2021 at 11:43 */
#pragma fieldalign shared2 __fault_type
typedef struct __fault_type
{
   char                            faultcode[32];
   char                            faultstring[32];
   char                            detail_rw[32];
} fault_type_def;
#define fault_type_def_Size 96
#pragma section body_type_02
/* Definition BODY-TYPE-02 created on 06/10/2021 at 11:43 */
#pragma fieldalign shared2 __body_type_02
typedef struct __body_type_02
{
   fault_type_def                  fault;
} body_type_02_def;
#define body_type_02_def_Size 96
#pragma section soapfault
/* Definition SOAPFAULT created on 06/10/2021 at 11:43 */
#pragma fieldalign shared2 __soapfault
typedef struct __soapfault
{
   body_type_02_def                body;
} soapfault_def;
#define soapfault_def_Size 96
#pragma section ics_transaction_rq
/* Definition ICS-TRANSACTION-RQ created on 06/10/2021 at 11:43 */
#pragma fieldalign shared2 __ics_transaction_rq
typedef struct __ics_transaction_rq
{
   lightwave_rq_header_def         lightwave_rq_header;
   request_message_soap_def        request_message_soap;
} ics_transaction_rq_def;
#define ics_transaction_rq_def_Size 1868
#pragma section ics_transaction_200_rp
/* Definition ICS-TRANSACTION-200-RP created on 06/10/2021 at 11:43 */
#pragma fieldalign shared2 __ics_transaction_200_rp
typedef struct __ics_transaction_200_rp
{
   lightwave_rp_header_def         lightwave_rp_header;
   reply_message_soap_def          reply_message_soap;
} ics_transaction_200_rp_def;
#define ics_transaction_200_rp_def_Size 352
#pragma section ics_transaction_500_rp
/* Definition ICS-TRANSACTION-500-RP created on 06/10/2021 at 11:43 */
#pragma fieldalign shared2 __ics_transaction_500_rp
typedef struct __ics_transaction_500_rp
{
   lightwave_rp_header_def         lightwave_rp_header;
   soapfault_def                   soapfault;
} ics_transaction_500_rp_def;
#define ics_transaction_500_rp_def_Size 128

