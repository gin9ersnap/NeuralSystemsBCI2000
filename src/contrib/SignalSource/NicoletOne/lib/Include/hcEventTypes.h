#ifndef __HCEVENTTYPES_H
#define __HCEVENTTYPES_H

// {A5A95616-A7F8-11cf-831A-0800091B5BDA}
static const GUID HCEVENT_PATIENT = 
{ 0xa5a95616, 0xa7f8, 0x11cf, { 0x83, 0x1a, 0x08, 0x00, 0x09, 0x1b, 0x5b, 0xda } };

// {08784382-C765-11d3-90CE-00104B6F4F70}
static const GUID HCEVENT_FORMATCHANGE = 
{ 0x8784382, 0xc765, 0x11d3, { 0x90, 0xce, 0x0, 0x10, 0x4b, 0x6f, 0x4f, 0x70 } };

// {09CBF740-C913-11d3-AE99-00104B6FC652}
static const GUID HCEVENT_ACQUISITION_OVERFLOW = 
{ 0x9cbf740, 0xc913, 0x11d3, { 0xae, 0x99, 0x0, 0x10, 0x4b, 0x6f, 0xc6, 0x52 } };

// {380A5E37-F32F-4eb3-9873-448ACA451C41}
static const GUID HCEVENT_RESYNC = 
{ 0x380a5e37, 0xf32f, 0x4eb3, { 0x98, 0x73, 0x44, 0x8a, 0xca, 0x45, 0x1c, 0x41 } };

// {A5A95617-A7F8-11cf-831A-0800091B5BDA}
static const GUID HCEVENT_IMPEDANCE_TEST = 
{ 0xa5a95617, 0xa7f8, 0x11cf, { 0x83, 0x1a, 0x08, 0x00, 0x09, 0x1b, 0x5b, 0xda } };

// {09CBF742-C913-11d3-AE99-00104B6FC652}
static const GUID HCEVENT_CAL = 
{ 0x9cbf742, 0xc913, 0x11d3, { 0xae, 0x99, 0x0, 0x10, 0x4b, 0x6f, 0xc6, 0x52 } };

// {7284B860-CD98-11d3-AE99-00104B6FC652}
static const GUID HCEVENT_DEBLOCK = 
{ 0x7284b860, 0xcd98, 0x11d3, { 0xae, 0x99, 0x0, 0x10, 0x4b, 0x6f, 0xc6, 0x52 } };

// {6FF394DA-D1B8-46da-B78F-866C67CF02AF}
static const GUID HCEVENT_PHOTIC = 
{ 0x6ff394da, 0xd1b8, 0x46da, { 0xb7, 0x8f, 0x86, 0x6c, 0x67, 0xcf, 0x2, 0xaf } };

// {A5A95610-A7F8-11cf-831A-0800091B5BDA}
static const GUID HCEVENT_PHOTIC_FLASH = 
{ 0xa5a95610, 0xa7f8, 0x11cf, { 0x83, 0x1a, 0x08, 0x00, 0x09, 0x1b, 0x5b, 0xda } };

//{A5A95608-A7F8-11cf-831A-0800091B5BDA}
static const GUID HCEVENT_HYPERVENTILATION = 
{ 0xa5a95608, 0xa7f8, 0x11cf, { 0x83, 0x1a, 0x08, 0x00, 0x09, 0x1b, 0x5b, 0xda } };

// {481DFC97-013C-4bc5-A203-871B0375A519}
static const GUID HCEVENT_POSTHYPERVENTILATION = 
{ 0x481dfc97, 0x13c, 0x4bc5, { 0xa2, 0x3, 0x87, 0x1b, 0x3, 0x75, 0xa5, 0x19 } };

// {F91416B8-16D4-4e4c-99E7-A6DF5ED5E6CF}
static const GUID HCEVENT_SOFTIMP = 
{ 0xf91416b8, 0x16d4, 0x4e4c, { 0x99, 0xe7, 0xa6, 0xdf, 0x5e, 0xd5, 0xe6, 0xcf } };

// A5A95646-A7F8-11cf-831A-0800091B5BDA
static const GUID HCEVENT_SEIZURE = 
{ 0xa5a95646, 0xa7f8, 0x11cf, { 0x83, 0x1a, 0x08, 0x00, 0x09, 0x1b, 0x5b, 0xda } };

// {C3B68051-EDCF-418c-8D53-27077B92DE22}
static const GUID HCEVENT_SPIKE =
{ 0xc3b68051, 0xedcf, 0x418c, { 0x8d, 0x53, 0x27, 0x7, 0x7b, 0x92, 0xde, 0x22 } };

// {5FFDF2FE-907D-47d0-B1CE-DAB7CC3AD42E}
static const GUID HCEVENT_SETUPCHANGE = 
{ 0x5ffdf2fe, 0x907d, 0x47d0, { 0xb1, 0xce, 0xda, 0xb7, 0xcc, 0x3a, 0xd4, 0x2e } };

// {0AFADB4A-34DD-41d2-B898-B52D23EABCA3}
static const GUID HCEVENT_REACTIONTIME_RANDOM = 
{ 0xafadb4a, 0x34dd, 0x41d2, { 0xb8, 0x98, 0xb5, 0x2d, 0x23, 0xea, 0xbc, 0xa3 } };

// {63E06FCC-E5BA-44d0-9556-BF5BB628127D}
static const GUID HCEVENT_REACTIONTIME_MANUAL = 
{ 0x63e06fcc, 0xe5ba, 0x44d0, { 0x95, 0x56, 0xbf, 0x5b, 0xb6, 0x28, 0x12, 0x7d } };

// {C90B7078-2612-43d5-83C1-65A0564B7167}
static const GUID HCEVENT_REACTIONTIME_EPILEPSY = 
{ 0xc90b7078, 0x2612, 0x43d5, { 0x83, 0xc1, 0x65, 0xa0, 0x56, 0x4b, 0x71, 0x67 } };

// {A5A95636-A7F8-11cf-831A-0800091B5BDA}
static const GUID HCEVENT_BRADYCARDIA = 
{ 0xA5A95636, 0xA7F8, 0x11cf, { 0x83, 0x1A, 0x08, 0x00, 0x09, 0x1B, 0x5B, 0xDA } };

// {A5A95637-A7F8-11cf-831A-0800091B5BDA}
static const GUID HCEVENT_TACHYCARDIA = 
{ 0xA5A95637, 0xA7F8, 0x11cf, { 0x83, 0x1A, 0x08, 0x00, 0x09, 0x1B, 0x5B, 0xDA } };

// {A5A95612-A7F8-11cf-831A-0800091B5BDA}
static const GUID HCEVENT_ANNOTATION = 
{ 0xA5A95612, 0xA7F8, 0x11cf, { 0x83, 0x1A, 0x08, 0x00, 0x09, 0x1B, 0x5B, 0xDA } };

// {A5A95645-A7F8-11cf-831A-0800091B5BDA}
static const GUID HCEVENT_ANNOTATION_DURATION = 
{ 0xA5A95645, 0xA7F8, 0x11cf, { 0x83, 0x1A, 0x08, 0x00, 0x09, 0x1B, 0x5B, 0xDA } };

// {A5A95609-A7F8-11cf-831A-0800091B5BDA}
static const GUID HCEVENT_PRINT =
{ 0xA5A95609, 0xA7F8, 0x11cf, { 0x83, 0x1A, 0x08, 0x00, 0x09, 0x1B, 0x5B, 0xDA } };

// {A71A6DB5-4150-48bf-B462-1C40521EBD6F}
static const GUID HCEVENT_DISCONNECT = 
{ 0xa71a6db5, 0x4150, 0x48bf, { 0xb4, 0x62, 0x1c, 0x40, 0x52, 0x1e, 0xbd, 0x6f } };

// {A74F00C4-BBBF-4c04-B012-7AD63841BC1A}
static const GUID HCEVENT_LOWDISK = 
{ 0xa74f00c4, 0xbbbf, 0x4c04, { 0xb0, 0x12, 0x7a, 0xd6, 0x38, 0x41, 0xbc, 0x1a } };

// {FCC022E0-4EA3-4ea7-853E-7B27552344A8}
static const GUID HCEVENT_OUTOFDISK = 
{ 0xfcc022e0, 0x4ea3, 0x4ea7, { 0x85, 0x3e, 0x7b, 0x27, 0x55, 0x23, 0x44, 0xa8 } };

// {8C400CF0-0A9A-44fc-9AF9-DC6987BD2B37}
static const GUID HCEVENT_XPOD_SENSOR_DISCONNECTED = 
{ 0x8c400cf0, 0xa9a, 0x44fc, { 0x9a, 0xf9, 0xdc, 0x69, 0x87, 0xbd, 0x2b, 0x37 } };

// {79F1C125-7D91-4757-A508-1B199879E672}
static const GUID HCEVENT_XPOD_STATUS = 
{ 0x79f1c125, 0x7d91, 0x4757, { 0xa5, 0x8, 0x1b, 0x19, 0x98, 0x79, 0xe6, 0x72 } };

// {6387C7C8-6F98-4886-9AF4-FA750ED300DE}
static const GUID HCEVENT_RECONNECT = 
{ 0x6387c7c8, 0x6f98, 0x4886, { 0x9a, 0xf4, 0xfa, 0x75, 0xe, 0xd3, 0x0, 0xde } };

// {A5A95635-A7F8-11CF-831A-0800091B5BDA}
static const GUID HCEVENT_DESAT =
{ 0xA5A95635, 0xA7F8, 0x11CF, { 0x83, 0x1A, 0x08, 0x00, 0x09, 0x1B, 0x5B, 0xDA } };

// {A5A95618-A7F8-11CF-831A-0800091B5BDA}
static const GUID HCEVENT_OBSTRUCTIVE_APNEA = 
{ 0xA5A95618, 0xA7F8, 0x11CF, { 0x83, 0x1A, 0x08, 0x00, 0x09, 0x1B, 0x5B, 0xDA} };

// {A5A95619-A7F8-11CF-831A-0800091B5BDA}
static const GUID HCEVENT_CENTRAL_APNEA = 
{ 0xA5A95619, 0xA7F8, 0x11CF, { 0x83, 0x1A, 0x08, 0x00, 0x09, 0x1B, 0x5B, 0xDA} };

// {A5A95620-A7F8-11CF-831A-0800091B5BDA}
static const GUID HCEVENT_MIXED_APNEA = 
{ 0xA5A95620, 0xA7F8, 0x11CF, { 0x83, 0x1A, 0x08, 0x00, 0x09, 0x1B, 0x5B, 0xDA} };

// {A5A95621-A7F8-11CF-831A-0800091B5BDA}
static const GUID HCEVENT_OBSTRUCTIVE_HYPOPNEA = 
{ 0xA5A95621, 0xA7F8, 0x11CF, { 0x83, 0x1A, 0x08, 0x00, 0x09, 0x1B, 0x5B, 0xDA } };

// {A5A95622-A7F8-11CF-831A-0800091B5BDA}
static const GUID HCEVENT_CENTRAL_HYPOPNEA = 
{ 0xA5A95622, 0xA7F8, 0x11CF, { 0x83, 0x1A, 0x08, 0x00, 0x09, 0x1B, 0x5B, 0xDA } };
   
// {A5A95623-A7F8-11CF-831A-0800091B5BDA}
static const GUID HCEVENT_MIXED_HYPOPNEA = 
{ 0xA5A95623, 0xA7F8, 0x11CF, { 0x83, 0x1A, 0x08, 0x00, 0x09, 0x1B, 0x5B, 0xDA } };

// {5B55D2E3-42D5-4643-852C-858F7FC705B6}
static const GUID HCEVENT_APNEA =
{ 0x5B55D2E3, 0x42D5, 0x4643, { 0x85, 0x2C, 0x85, 0x8F, 0x7F, 0xC7, 0x05, 0xB6 } };

// {5211C17C-0E41-477E-8D40-1E94621E43F1}
static const GUID HCEVENT_HYPOPNEA = 
{ 0x5211C17C, 0x0E41, 0x477E, { 0x8D, 0x40, 0x1E, 0x94, 0x62, 0x1E, 0x43, 0xF1 } };

// {9723B2B9-9366-4b6b-A560-6AAB82D89577}
static const GUID HCEVENT_DATEX = 
{ 0x9723b2b9, 0x9366, 0x4b6b, { 0xa5, 0x60, 0x6a, 0xab, 0x82, 0xd8, 0x95, 0x77 } };

// {0A205CD4-1480-4F02-8AFF-4E4CD3B21078}
static const GUID HCEVENT_ARTIFACT =
{ 0x0A205CD4, 0x1480, 0x4F02, { 0x8A, 0xFF, 0x4E, 0x4C, 0xD3, 0xB2, 0x10, 0x78 } };

// {D864246C-120D-4999-BCED-66768FFFAFC5}
static const GUID HCEVENT_INVALID_DATA = 
{ 0xd864246c, 0x120d, 0x4999, { 0xbc, 0xed, 0x66, 0x76, 0x8f, 0xff, 0xaf, 0xc5 } };

// {A9C30C75-6B7B-478d-9B21-6A74ABF645CD}
static const GUID HCEVENT_SHUNT = 
{ 0xa9c30c75, 0x6b7b, 0x478d, { 0x9b, 0x21, 0x6a, 0x74, 0xab, 0xf6, 0x45, 0xcd } };

// {0E683672-9EDA-4a51-97E7-77F14547CD9A}
static const GUID HCEVENT_CLAMP_CAROTIS_LEFT = 
{ 0xe683672, 0x9eda, 0x4a51, { 0x97, 0xe7, 0x77, 0xf1, 0x45, 0x47, 0xcd, 0x9a } };

// {3DE6F6A4-5DAD-4889-84FF-43BAB0ADB373}
static const GUID HCEVENT_CLAMP_CAROTIS_RIGHT = 
{ 0x3de6f6a4, 0x5dad, 0x4889, { 0x84, 0xff, 0x43, 0xba, 0xb0, 0xad, 0xb3, 0x73 } };

// {5BCF0A32-5B72-4c24-8F98-064CC54122A0}
static const GUID HCEVENT_PERFUSION = 
{ 0x5bcf0a32, 0x5b72, 0x4c24, { 0x8f, 0x98, 0x6, 0x4c, 0xc5, 0x41, 0x22, 0xa0 } };

// {9BF89B17-6FF2-4e5e-A321-BE24C65CF5D4}
static const GUID HCEVENT_AORTA_CLAMP = 
{ 0x9bf89b17, 0x6ff2, 0x4e5e, { 0xa3, 0x21, 0xbe, 0x24, 0xc6, 0x5c, 0xf5, 0xd4 } };

#endif
