#include <windows.h>
#include <stdio.h>

int main() {
    SYSTEM_POWER_STATUS bstatus;

    if(GetSystemPowerStatus(&bstatus)) {
        printf("Battery: %d%%", bstatus.BatteryLifePercent);
    }

    system("pause >nul");
    return 0;
}