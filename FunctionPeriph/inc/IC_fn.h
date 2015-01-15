#ifndef __IC_FN_H
#define __IC_FN_H

u8 Set_Settings_DA12(u8 t);
u8 Set_Settings_DA6(u8 t);
u8 Set_Settings_DA2(u8 t);
u8 Set_Settings_DA8(u8 t);
u8 Set_Settings_FD(u8 t, _SETTINGSOFCHANNEL *channel_settings);

u8 Set_Default_Settings(_SETTINGSOFCHANNEL *channel_settings );
u8 Read_Number_of_Channel (void);

#endif