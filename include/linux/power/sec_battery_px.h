/*
 *  sec_battery.h
 *  charger systems for lithium-ion (Li+) batteries
 *
 *  Copyright (C) 2010 Samsung Electronics
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef _LINUX_SEC_BATTERY_H
#define _LINUX_SEC_BATTERY_H

enum charger_type {
	CHARGER_BATTERY = 0,
	CHARGER_USB,
	CHARGER_AC,
	CHARGER_DOCK,
	CHARGER_MISC,
	CHARGER_DISCHARGE
};

struct max8903_charger_data {
	int enable_line;
	int connect_line;
	int fullcharge_line;
	int currentset_line;
	int accessory_line;
};

struct sec_battery_platform_data {
	struct max8903_charger_data charger;

	void (*set_charging_state) (int, int);
	int (*get_charging_state) (void);
	void (*set_charging_current) (int);
	int (*get_charging_current) (void);
	int (*get_charger_is_full)(void);

	void (*init_charger_gpio) (void);
	void (*inform_charger_connection) (int);
	int temp_high_threshold;
	int temp_high_recovery;
	int temp_low_recovery;
	int temp_low_threshold;
	int charge_duration;
	int recharge_duration;
	int recharge_voltage;
	int (*check_lp_charging_boot) (void);
	int (*check_jig_status) (void);

};

/* for test driver */
#define __TEST_DEVICE_DRIVER__

extern int low_batt_compensation(int fg_soc, int fg_vcell, int fg_current);
extern void reset_low_batt_comp_cnt(void);
extern int get_fuelgauge_value(int data);
extern struct max17042_chip *max17042_chip_data;

#if defined(CONFIG_STMPE811_ADC)
u16 stmpe811_get_adc_data(u8 channel);
#endif

#endif
