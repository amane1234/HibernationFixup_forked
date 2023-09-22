// kern_config.hpp
// HibernationFixup
// Copyright © 2016-2017 lvs1974. All rights reserved.

#ifndef kern_config_private_h
#define kern_config_private_h

#include <Headers/kern_util.hpp>

class Configuration {
public:
    // Possible boot arguments
    static const char *bootargOff[];
    static const char *bootargDebug[];
    static const char *bootargBeta[];
    static constexpr const char *bootargDumpNvram         {"-hbfx-dump-nvram"};          // Write NVRAM to file
    static constexpr const char *bootargDisablePatchPCI   {"-hbfx-disable-patch-pci"};   // Disable patch PCI family
    static constexpr const char *bootargPatchPCIWithList  {"hbfx-patch-pci"};            // Patch PCI family ignored device list
    static constexpr const char *bootargAutoHibernateMode {"hbfx-ahbm"};                 // Auto hibernate mode

public:
    // Retrieve boot arguments
    void readArguments();

    // Dump NVRAM to /nvram.plist
    bool dumpNvram {false};

    // Patch PCI Family
    bool patchPCIFamily {true};

    // Device list (can be separated by comma, space, or something similar)
    char ignored_device_list[64] {};

    // Flags used to control automatic hibernation behavior (takes place only when the system goes to sleep)
    enum AutoHibernateModes {
        EnableAutoHibernation           = 1,
        WhenLidIsClosed                 = 2,
        WhenExternalPowerIsDisconnected = 4,
        WhenBatteryIsNotCharging        = 8,
        WhenBatteryIsAtWarnLevel        = 16,
        WhenBatteryAtCriticalLevel      = 32,
        DoNotOverrideWakeUpTime         = 64,
        DisableStimulusDarkWakeActivityTickle = 128,

        // Next 4 bits are used to specify minimal capacity percent remaining value when hibernation will be forced.
        RemainCapacityBit1				= 256,
        RemainCapacityBit2				= 512,
        RemainCapacityBit3				= 1024,
        RemainCapacityBit4				= 2048
    };

    int autoHibernateMode {0};

    Configuration() = default;
};

extern Configuration ADDPR(hbfx_config);

#endif
