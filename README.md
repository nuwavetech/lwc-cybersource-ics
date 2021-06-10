# LightWave Client CyberSource ICS Sample
This LightWave Client sample illustrates how to submit transaction requests to
the CyberSource Internet Commerce Suite (ICS) web service.

Note that CyberSource ICS is a SOAP web service. While LightWave Client is designed
to access REST web services, because it supports JSON & XML, many SOAP web services can
be accessed successfully by defining the SOAP message as you would with any other XML message.
LightWave Client is not able to import SOAP web service definitions
from WSDL. SOAP messages must be added to the API defintion by example as is the
case with all other API message types.

Please note:

- See section 2 of the CyberSource SOAP Toolkits for Web Services Developer Guide for information
about accessing the CyberSource ICS service.
- The sample sends the SOAP Message Sample found in section 2 of the Guide. This request will
always return a REJECT status, but verifies that the service can be accessed.
- In order to use the sample, you must obtain your own CyberSource merchant ID and transaction key.
- The sample uses version 1.181 of the API. To use another version, modify the API definition to
use the namespace of the API version you are using. This can be achieved by editing the CSICSAPI
file and replacing all occurances of "1.181" with your API version.

## Related Documentation
- [LightWave Client](https://docs.nuwavetech.com/display/LWCLIENT)
- [CyberSource SOAP Toolkits for Web Services Developer Guide](https://developer.cybersource.com/library/documentation/dev_guides/SOAP_Toolkits/SOAP_toolkits.pdf)
- [CyberSource SOAP Toolkit Samples on GitHub](https://github.com/CyberSource/cybersource-soap-toolkit)

## Sample Prerequisites

+ NonStop C Compiler.
+ An installed instance of [LightWave Client](https://docs.nuwavetech.com/display/LWCLIENT) version **1.2.1** or greater.
+ A CyberSource merchant ID and transaction key.

The following values must be configured in the SETENV TACL macro after UNPAKing the sample files:

+ lwc-isv - The installation subvolume of your LightWave Client software.
+ base-url - The base URL of you the ICS web service. See Section 2 of the ICS SOAP Toolkit Guide.

The values for pathmon-name and server-class may also be customized
if they are not appropriate for your system.

## Install & Build

The CSICS sample client must be built from source. The source files are present in the repository for convenient viewing.
In addition, a PAK archive containing all of the source files is available for transfer to your NonStop system.

| Repository File | NonStop File |
| -- | -- |
| macros/build.txt | build |
| macros/loadddl.txt | loadddl |
| macros/logcfg.txt | logcfg |
| macros/setenv.txt | setenv |
| macros/startpw.txt | startpw |
| macros/stoppw.txt | stoppw |
| macros/unsetenv.txt | unsetenv |
| resources/csicsapi.json | csicsapi |
| resources/csicsddl.txt | csicsddl |
| src/csics.c | csicsc |
| csicspak.bin | csicspak |

#### Transfer the PAK archive to your NonStop System

Download `csicspak.bin` from this repository to your local system, then upload to your NonStop server using binary transfer mode.

Note: to download the PAK file, click `csicspak.bin` in the file list to display the file details, then click the *Download* button.

Logon to TACL on your NonStop system to peform the installation and build steps.

#### Unpak the PAK archive
```
TACL > UNPAK csicspak ($*.*.*), VOL $vol.subvol, LISTALL, MYID
```

#### Update the merchant ID and transaction key
The CSICSC program source contains placeholders for your merchant ID and transaction key. Edit
the source file and update the placeholders with your ID and key. Note that the transaction key
string is too long for a single edit file line and must be split across multiple lines. Use
caution when splitting the key string.
```
#define YOUR_MERCHANT_ID "your-merchant-id"
#define YOUR_TRANSACTION_KEY                                                    \
  "WB3NEkcF6Kw.......  your transaction key ....... F3836nm1qC1/H0ZaTERakv7QUs" \
  "oopcwVRLfmanQf15cBFbVTmmQcTS1CRWxZLvAHrY66w+XfRm0+Qg84KIN3tKZ5M8X9nfyjTkqQI" \
  "QscTFJFweGBh9deR+mZl+nIeL912TLeMIVowGX6zMdtyHF3ixWJ1uEt6JVp6VjS92KgS71xHdF9" \
  "KMTClX4XwltQoXdmw6BlwELTepJcbV3Jj1DUumEYC6f5OsOtplFadUfF9LrqOlD1alWPMMIg4BT" \
  "2+3tSyFPuEOJ3K++74fPQB6OAtco66A0J2MtzMPZsw=="
```

#### Build the application
```
TACL > RUN LOADDDL
TACL > RUN BUILD
```
## Running the application
Customize the SETENV macro for your environment and run the macro to set the required PARAMs.
```
TACL> T/EDIT SETENV
TACL> RUN SETENV
```
Start the LightWave Client Pathway
```
TACL > RUN STARTPW
```
Run the application.
```
TACL> run csics

LightWave Client(tm) - CyberSource Internet Commerce Suite (ICS) sample client.

Transaction completed:
  Request ID:  6233461738666268603011
  Decision:    REJECT
  Reason Code: 202

Request completed in 0.311445 seconds.

```
When done with the sample, stop the LightWave Client Pathway.
```
TACL> RUN STOPPW
```