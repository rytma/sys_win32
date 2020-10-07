// https://docs.microsoft.com/en-us/windows/desktop/sysinfo/enumerating-registry-subkeys

/**
 * Like other files and servces in Windows, all registry keys may be
 * restricted by access control lists (ACLs), depending on user
 * privileges, or on security tokens acquired by applications, or
 * on system security policies enforced by the system.
*/


#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383

/**
 * These are seven predefined root keys, traditionally named according
 * to their constant handles defined in the Win32 API, or by synonymous
 * abbreviations (depending on application):
 * 
 * - HKEY_PERFORMANCE_DATA  (only in Windows NT, but invisible in the Windows Registry Editor)
 * - HKEY_DYN_DATA          (only in Windows 9x, and visible in the Windows Registry Editor)
*/
HKEY regkey[] = {
    HKEY_LOCAL_MACHINE,     // HKLM
    HKEY_USERS,             // HKU
    HKEY_CURRENT_USER,      // HKCU
    HKEY_CURRENT_CONFIG,    // HKCC
    HKEY_CLASSES_ROOT       // HKCR
};

void query_key(HKEY hKey) {
    char achKey[MAX_KEY_LENGTH];    // buffer for subkey
    unsigned long cbName;           // size of name string
    char achClass[MAX_PATH] = "";   // buffer for class name
    unsigned long cchClassName = MAX_PATH;  // size of class string
    unsigned long cSubKeys = 0;     // number of subkeys
    unsigned long cbMaxSubKey;      // longest subkey size
    unsigned long cchMaxClass;      // longest class string
    unsigned long cValues;          // number of values for key
    unsigned long cchMaxValue;      // longest value name
    unsigned long cbMaxValueData;   // longest value data
    unsigned long cbSecurityDescriptor; // size of security descriptor
    FILETIME ftLastWriteTime;       // last write time

    unsigned long i, ret;

    char achValue[MAX_VALUE_NAME];
    unsigned long cchValue = MAX_VALUE_NAME;

    ret = RegQueryInfoKey(
        hKey,                       // key handle
        achClass,                   // buffer for class name
        &cchClassName,              // size of class string
        NULL,                       // reserved
        &cSubKeys,                  // number of subkeys
        &cbMaxSubKey,               // longest subkey size
        &cchMaxClass,               // longest class string
        &cValues,                   // number of values for this key
        &cchMaxValue,               // longest value name
        &cbMaxValueData,            // longest value data
        &cbSecurityDescriptor,      // security descriptor
        &ftLastWriteTime            // last write time
    );

    if (cSubKeys) {
        printf("Number of subkeys: %d\n", cSubKeys);

        for (i = 0; i < cSubKeys; i++) {
            cbName = MAX_KEY_LENGTH;
            ret = RegEnumKeyEx(
                hKey,
                i,
                achKey,
                &cbName,
                NULL,
                NULL,
                NULL,
                &ftLastWriteTime
            );
            if (ret == ERROR_SUCCESS) {
                printf("(%d) %s\n", i + 1, achKey);
            }
        }
    }

    if (cValues) {
        printf("\nNumber of values: %d\n", cValues);

        for (i = 0, ret = ERROR_SUCCESS; i < cValues; i++) {
            cchValue = MAX_VALUE_NAME;
            achValue[0] = '\0';
            ret = RegEnumValue(
                hKey,
                i,
                achValue,
                &cchValue,
                NULL,
                NULL,
                NULL,
                NULL
            );
            if (ret == ERROR_SUCCESS) {
                printf("(%d) %s\n", i + 1, achValue);
            }
        }
    }
}

int main(int argc, char **argv) {
    HKEY hTestKey;

    if (RegOpenKeyEx(
                regkey[0],
                argv[1],
                0,
                KEY_READ,
                &hTestKey) == ERROR_SUCCESS) {
        query_key(hTestKey);
    }

    RegCloseKey(hTestKey);

    return 0;
}