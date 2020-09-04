/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycodes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 18:58:28 by amalliar          #+#    #+#             */
/*   Updated: 2020/09/04 09:27:33 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYCODES_H
# define KEYCODES_H

/*
**  Summary:
**    Virtual keycodes
**
**  Discussion:
**    These constants are the virtual keycodes defined originally in
**    Inside Mac Volume V, pg. V-191. They identify physical keys on a
**    keyboard. Those constants with "ANSI" in the name are labeled
**    according to the key position on an ANSI-standard US keyboard.
**    For example, kVK_ANSI_A indicates the virtual keycode for the key
**    with the letter 'A' in the US keyboard layout. Other keyboard
**    layouts may have the 'A' key label on a different physical key;
**    in this case, pressing 'A' will generate a different virtual
**    keycode.
*/

# define KVK_ANSI_A					0x00
# define KVK_ANSI_S					0x01
# define KVK_ANSI_D					0x02
# define KVK_ANSI_F					0x03
# define KVK_ANSI_H					0x04
# define KVK_ANSI_G					0x05
# define KVK_ANSI_Z					0x06
# define KVK_ANSI_X					0x07
# define KVK_ANSI_C					0x08
# define KVK_ANSI_V					0x09
# define KVK_ANSI_B					0x0B
# define KVK_ANSI_Q					0x0C
# define KVK_ANSI_W					0x0D
# define KVK_ANSI_E					0x0E
# define KVK_ANSI_R					0x0F
# define KVK_ANSI_Y					0x10
# define KVK_ANSI_T					0x11
# define KVK_ANSI_1					0x12
# define KVK_ANSI_2					0x13
# define KVK_ANSI_3					0x14
# define KVK_ANSI_4					0x15
# define KVK_ANSI_6					0x16
# define KVK_ANSI_5					0x17
# define KVK_ANSI_EQUAL				0x18
# define KVK_ANSI_9					0x19
# define KVK_ANSI_7					0x1A
# define KVK_ANSI_MINUS				0x1B
# define KVK_ANSI_8					0x1C
# define KVK_ANSI_0					0x1D
# define KVK_ANSI_RIGHTBRACKET		0x1E
# define KVK_ANSI_O					0x1F
# define KVK_ANSI_U					0x20
# define KVK_ANSI_LEFTBRACKET		0x21
# define KVK_ANSI_I					0x22
# define KVK_ANSI_P					0x23
# define KVK_ANSI_L					0x25
# define KVK_ANSI_J					0x26
# define KVK_ANSI_QUOTE				0x27
# define KVK_ANSI_K					0x28
# define KVK_ANSI_SEMICOLON			0x29
# define KVK_ANSI_BACKSLASH			0x2A
# define KVK_ANSI_COMMA				0x2B
# define KVK_ANSI_SLASH				0x2C
# define KVK_ANSI_N					0x2D
# define KVK_ANSI_M					0x2E
# define KVK_ANSI_PERIOD			0x2F
# define KVK_ANSI_GRAVE				0x32
# define KVK_ANSI_KEYPADDECIMAL		0x41
# define KVK_ANSI_KEYPADMULTIPLY	0x43
# define KVK_ANSI_KEYPADPLUS		0x45
# define KVK_ANSI_KEYPADCLEAR		0x47
# define KVK_ANSI_KEYPADDIVIDE		0x4B
# define KVK_ANSI_KEYPADENTER		0x4C
# define KVK_ANSI_KEYPADMINUS		0x4E
# define KVK_ANSI_KEYPADEQUALS		0x51
# define KVK_ANSI_KEYPAD0			0x52
# define KVK_ANSI_KEYPAD1			0x53
# define KVK_ANSI_KEYPAD2			0x54
# define KVK_ANSI_KEYPAD3			0x55
# define KVK_ANSI_KEYPAD4			0x56
# define KVK_ANSI_KEYPAD5			0x57
# define KVK_ANSI_KEYPAD6			0x58
# define KVK_ANSI_KEYPAD7			0x59
# define KVK_ANSI_KEYPAD8			0x5B
# define KVK_ANSI_KEYPAD9			0x5C

/*
** Keycodes for keys that are independent of keyboard layout.
*/

# define KVK_RETURN					0x24
# define KVK_TAB					0x30
# define KVK_SPACE					0x31
# define KVK_DELETE					0x33
# define KVK_ESCAPE					0x35
# define KVK_COMMAND				0x37
# define KVK_SHIFT					0x38
# define KVK_CAPSLOCK				0x39
# define KVK_OPTION					0x3A
# define KVK_CONTROL				0x100
# define KVK_RIGHTCOMMAND			0x36
# define KVK_RIGHTSHIFT				0x3C
# define KVK_RIGHTOPTION			0x3D
# define KVK_RIGHTCONTROL			0x3E
# define KVK_FUNCTION				0x3F
# define KVK_F17					0x40
# define KVK_VOLUMEUP				0x48
# define KVK_VOLUMEDOWN				0x49
# define KVK_MUTE					0x4A
# define KVK_F18					0x4F
# define KVK_F19					0x50
# define KVK_F20					0x5A
# define KVK_F5						0x60
# define KVK_F6						0x61
# define KVK_F7						0x62
# define KVK_F3						0x63
# define KVK_F8						0x64
# define KVK_F9						0x65
# define KVK_F11					0x67
# define KVK_F13					0x69
# define KVK_F16					0x6A
# define KVK_F14					0x6B
# define KVK_F10					0x6D
# define KVK_F12					0x6F
# define KVK_F15					0x71
# define KVK_HELP					0x72
# define KVK_HOME					0x73
# define KVK_PAGEUP					0x74
# define KVK_FORWARDDELETE			0x75
# define KVK_F4						0x76
# define KVK_END					0x77
# define KVK_F2						0x78
# define KVK_PAGEDOWN				0x79
# define KVK_F1						0x7A
# define KVK_LEFTARROW				0x7B
# define KVK_RIGHTARROW				0x7C
# define KVK_DOWNARROW				0x7D
# define KVK_UPARROW				0x7E

#endif
