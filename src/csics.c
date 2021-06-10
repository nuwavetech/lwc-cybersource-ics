/**
 *
 *  Copyright (c) 2021 NuWave Technologies, Inc. All rights reserved.
 *
 *  MIT License
 *  https://github.com/nuwavetech/lwc-cybersource-ics/blob/main/LICENSE
 *
 */

#pragma nolist
#include <cextdecs>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <tal.h>
#pragma list

#include "csics.h"

#define YOUR_MERCHANT_ID "your-merchant-id"
#define YOUR_TRANSACTION_KEY                                                    \
  "WB3NEkcF6Kw.......  your transaction key ....... F3836nm1qC1/H0ZaTERakv7QUs" \
  "oopcwVRLfmanQf15cBFbVTmmQcTS1CRWxZLvAHrY66w+XfRm0+Qg84KIN3tKZ5M8X9nfyjTkqQI" \
  "QscTFJFweGBh9deR+mZl+nIeL912TLeMIVowGX6zMdtyHF3ixWJ1uEt6JVp6VjS92KgS71xHdF9" \
  "KMTClX4XwltQoXdmw6BlwELTepJcbV3Jj1DUumEYC6f5OsOtplFadUfF9LrqOlD1alWPMMIg4BT" \
  "2+3tSyFPuEOJ3K++74fPQB6OAtco66A0J2MtzMPZsw=="

static const char* get_env_value(const char* name, int required);
static void print_send_error(void);
static void send_transaction(const char* pathmon_name,
                             const char* server_class);

/* A convenience macro to shorten line length. */
#define CPY(d, s) strncpy(d, s, (sizeof(d) - 1))

int main(int argc, char** argv, char** env) {
  const char* pathmon_name;
  const char* server_class;

  printf(
      "\nLightWave Client(tm) - CyberSource Internet Commerce Suite (ICS) sample client.\n");

  /* Get variables from the environment. These are set by the SETENV macro. */
  if ((pathmon_name = get_env_value("PATHMON-NAME", 1)) == NULL) {
    return 0;
  }

  if ((server_class = get_env_value("SERVER-CLASS", 1)) == NULL) {
    return 0;
  }

  send_transaction(pathmon_name, server_class);

  return 0;
}

static const char* get_env_value(const char* name, int required) {
  const char* v = getenv(name);
  if (v == NULL && required != 0) {
    printf("PARAM \"%s\" not set. Did you run SETENV?\n", name);
  }
  return v;
}

static void send_transaction(const char* pathmon_name,
                             const char* server_class) {
  long long start_time;
  long long end_time;
  int reply_len;
  short rc;
  ics_transaction_rq_def ics_transaction_rq;
  request_message_type_def* request_message;
  username_token_type_def* username_token;

  union {
    lightwave_rp_header_def header;
    ics_transaction_200_rp_def rp_200;
    ics_transaction_500_rp_def rp_fault;
  } ics_transaction_rp;

  /* Build the transaction reqeust. */
  memset(&ics_transaction_rq, 0, sizeof(ics_transaction_rq));
  ics_transaction_rq.lightwave_rq_header.rq_code = rq_ics_transaction;

  username_token = &ics_transaction_rq.request_message_soap.header.security_rw
                        .username_token;
  CPY(username_token->username, YOUR_MERCHANT_ID);
  CPY(username_token->password, YOUR_TRANSACTION_KEY);

  request_message =
      &ics_transaction_rq.request_message_soap.body.request_message;
  CPY(request_message->merchant_id, YOUR_MERCHANT_ID);
  CPY(request_message->merchant_reference_code, "MRC-123");
  CPY(request_message->bill_to.first_name, "John");
  CPY(request_message->bill_to.last_name, "Doe");
  CPY(request_message->bill_to.street_1, "1295 Charlston Road");
  CPY(request_message->bill_to.city, "Mountain View");
  CPY(request_message->bill_to.state, "CA");
  CPY(request_message->bill_to.postal_code, "94043");
  CPY(request_message->bill_to.country, "US");
  CPY(request_message->bill_to.email, "null@cybersource.com");

  request_message->item_count = 2;
  CPY(request_message->item[0].id, "0");
  CPY(request_message->item[0].unit_price, "5.00");
  request_message->item[0].quantity = 1;

  CPY(request_message->item[1].id, "1");
  CPY(request_message->item[1].unit_price, "10.00");
  request_message->item[1].quantity = 2;

  CPY(request_message->purchase_totals.currency_rw, "USD");

  CPY(request_message->card.account_number, "4111111111111111");
  CPY(request_message->card.expiration_month, "11");
  CPY(request_message->card.expiration_year, "2020");

  CPY(request_message->cc_auth_service.run_rw, "true");

  start_time = JULIANTIMESTAMP();

  rc = SERVERCLASS_SENDL_(
      (char*)pathmon_name, (short)strlen(pathmon_name), (char*)server_class,
      (short)strlen(server_class), (char*)&ics_transaction_rq,
      (char*)&ics_transaction_rp, sizeof(ics_transaction_rq),
      sizeof(ics_transaction_rp), &reply_len);

  end_time = JULIANTIMESTAMP();

  /* Pathway error? */
  if (rc != 0) {
    print_send_error();
    return;
  }

  /* Output the results. */
  if (ics_transaction_rp.header.http_status == 200) {
    reply_message_type_def* reply_message;

    reply_message =
        &ics_transaction_rp.rp_200.reply_message_soap.body.reply_message;

    printf("\nTransaction completed:\n");
    printf("  Request ID:  %s\n", reply_message->request_id);
    printf("  Decision:    %s\n", reply_message->decision);
    printf("  Reason Code: %d\n\n", reply_message->reason_code);
  } else if (ics_transaction_rp.header.http_status == 500) {
    fault_type_def* fault;

    fault = &ics_transaction_rp.rp_fault.soapfault.body.fault;

    printf("\nSOAP Fault occured:\n");
    printf("  Fault Code:   %s\n", fault->faultcode);
    printf("  Fault String: %s\n\n", fault->faultstring);
  } else {
    printf("\nUnexpected HTTP error %d occured.\n\n",
           ics_transaction_rp.header.http_status);
  }

  printf("Request completed in %g seconds.\n\n",
         (double)(end_time - start_time) / 1000000.0);

  return;
}

static void print_send_error(void) {
  short prc;
  short frc;

  SERVERCLASS_SEND_INFO_(&prc, &frc);

  printf("\n\nSERVERCLASS_SEND_ error %hd:%hd occurred.\n\n", prc, frc);
  switch (frc) {
  case 14:
    printf("Did you start the pathway by running STARTPW?\n\n");
    break;
  default:
    break;
  }

  return;
}

/* End of file. */