#ifndef NC_DEF_HPP
#define NC_DEF_HPP

// --<type_alias>--
// --number
using Int8 = __int8;
using Int16 = __int16;
using Int32 = __int32;
using Int64 = __int64;
using UInt8 = unsigned __int8;
using UInt16 = unsigned short;
using UInt32 = unsigned int;
using UInt64 = unsigned long int;
using Float32 = float;
using Float64 = double;
using Float128 = long double;
// --string
using Char = char;
using WChar = wchar_t;
using UChar = unsigned char;
using CString = const char*;
using String = std::basic_string<char, std::char_traits<char>, std::allocator<char>>;
using WString = std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t>>;
// --memory
using Byte = char;
using UByte = unsigned char;
using Size = size_t;
namespace NC
{
	// --memory
	template <typename RefType> using RefOwner = std::unique_ptr<RefType>;
	template <typename RefType> using RefKeeper = std::shared_ptr<RefType>;
	// --container
	template <typename ValType, size_t szCount> using SArray = std::array<ValType, szCount>;
	template <typename ValType> using DArray = std::vector<ValType>;
	template <typename ValType> using List2 = std::list<ValType>;
	template <typename ValType> using DStack = std::stack<ValType>;
	// --platform
#if (defined NC_PLATFORM_WINDOWS  || defined NCW_PLATFORM_WINDOWS)
	using CHistoryInfo = CONSOLE_HISTORY_INFO;
	using CSelectionInfo = CONSOLE_SELECTION_INFO;
	using CFrameBufInfo = CONSOLE_SCREEN_BUFFER_INFOEX;
	using CPixelInfo = CONSOLE_FONT_INFOEX;
	using CPixel = CHAR_INFO;
	using V2xy = COORD;
	using V2wh = COORD;
	using V4xywh = SMALL_RECT;
#endif	// NC_PLATFORM
}
// --</type_alias>--

// ========<key_codes_nc>========
#define NC_KEY_NONE					0
// Printable keys
#define NC_KEY_SPACE_32				32
#define NC_KEY_APOSTROPHE_39		39
#define NC_KEY_COMMA_44				44
#define NC_KEY_MINUS_45				45
#define NC_KEY_PERIOD_46			46
#define NC_KEY_SLASH_47				47
#define NC_KEY_0_48					48
#define NC_KEY_1_49					49
#define NC_KEY_2_50					50
#define NC_KEY_3_51					51
#define NC_KEY_4_52					52
#define NC_KEY_5_53					53
#define NC_KEY_6_54					54
#define NC_KEY_7_55					55
#define NC_KEY_8_56					56
#define NC_KEY_9_57					57
#define NC_KEY_SEMICOLON_59			59
#define NC_KEY_EQUAL_61				61
// Alphabet_upper_case
#define NC_KEY_A_65					65
#define NC_KEY_B_66					66
#define NC_KEY_C_67					67
#define NC_KEY_D_68					68
#define NC_KEY_E_69					69
#define NC_KEY_F_70					70
#define NC_KEY_G_71					71
#define NC_KEY_H_72					72
#define NC_KEY_I_73					73
#define NC_KEY_J_74					74
#define NC_KEY_K_75					75
#define NC_KEY_L_76					76
#define NC_KEY_M_77					77
#define NC_KEY_N_78					78
#define NC_KEY_O_79					79
#define NC_KEY_P_80					80
#define NC_KEY_Q_81					81
#define NC_KEY_R_82					82
#define NC_KEY_S_83					83
#define NC_KEY_T_84					84
#define NC_KEY_U_85					85
#define NC_KEY_V_86					86
#define NC_KEY_W_87					87
#define NC_KEY_X_88					88
#define NC_KEY_Y_89					89
#define NC_KEY_Z_90					90
// Additional
#define NC_KEY_LEFT_BRACKET_91		91
#define NC_KEY_BACKSLASH_92			92
#define NC_KEY_RIGHT_BRACKET_93		93
// Alphabet_lower_case
#define NC_KEY_a_97					97
#define NC_KEY_b_98					98
#define NC_KEY_c_99					99
#define NC_KEY_d_100				100
#define NC_KEY_e_101				101
#define NC_KEY_f_102				102
#define NC_KEY_g_103				103
#define NC_KEY_h_104				104
#define NC_KEY_i_105				105
#define NC_KEY_j_106				106
#define NC_KEY_k_107				107
#define NC_KEY_l_108				108
#define NC_KEY_m_109				109
#define NC_KEY_n_110				110
#define NC_KEY_o_111				111
#define NC_KEY_p_112				112
#define NC_KEY_q_113				113
#define NC_KEY_r_114				114
#define NC_KEY_s_115				115
#define NC_KEY_t_116				116
#define NC_KEY_u_117				117
#define NC_KEY_v_118				118
#define NC_KEY_w_119				119
#define NC_KEY_x_120				120
#define NC_KEY_y_121				121
#define NC_KEY_z_122				122
// Functional keys
#define NC_KEY_ESCAPE_27			27
#define NC_KEY_BACKSPACE_8			8
#define NC_KEY_HTAB_9				9
#define NC_KEY_ENTER_13				13
#define NC_KEY_HTAB_11				11
#define NC_KEY_INS_45				45            
#define NC_KEY_DEL_46				46
#define NC_KEY_RIGHT_38				39
#define NC_KEY_LEFT_37				37
#define NC_KEY_DOWN_40				40
#define NC_KEY_UP_38				38
#define NC_KEY_F1					' '
#define NC_KEY_F2					' '
#define NC_KEY_F3					' '
#define NC_KEY_F4					' '
#define NC_KEY_F5					' '
#define NC_KEY_F6					' '
#define NC_KEY_F7					' '
#define NC_KEY_F8					' '
#define NC_KEY_F9					' '
#define NC_KEY_F10					' '
#define NC_KEY_F11					' '
#define NC_KEY_F12					' '
#define NC_KEY_KP_0					' '
#define NC_KEY_KP_1					' '
#define NC_KEY_KP_2					' '
#define NC_KEY_KP_3					' '
#define NC_KEY_KP_4					' '
#define NC_KEY_KP_5					' '
#define NC_KEY_KP_6					' '
#define NC_KEY_KP_7					' '
#define NC_KEY_KP_8					' '
#define NC_KEY_KP_9					' '
#define NC_KEY_KP_DECIMAL			' '
#define NC_KEY_KP_DIVIDE			' '
#define NC_KEY_KP_MULTIPLY			' '
#define NC_KEY_KP_SUBTRACT			' '
#define NC_KEY_KP_ADD				' '
#define NC_KEY_KP_ENTER_13			' '
#define NC_KEY_KP_EQUAL				' '
#define NC_KEY_SHIFT_LEFT			16
#define NC_KEY_SHIFT_RIGHT			16
#define NC_KEY_CONTROL_LEFT			17
#define NC_KEY_CONTROL_RIGHT		17
#define NC_KEY_ALT_LEFT				18
#define NC_KEY_ALT_RIGHT			18

#define NC_KEY_LAST					256
// ========</key_codes_nc>========

// ========<device_codes_nc>========
#define NC_MS_BTN_0				0
#define NC_MS_BTN_1				1
#define NC_MS_BTN_2				2
#define NC_MS_BTN_3				3
#define NC_MS_BTN_4				4
#define NC_MS_BTN_5				5
#define NC_MS_BTN_6				6
#define NC_MS_BTN_7				7
#define NC_MS_BTN_LAST			NC_MS_BTN_7
#define NC_MS_BTN_LEFT			NC_MS_BTN_0
#define NC_MS_BTN_RIGHT			NC_MS_BTN_1
#define NC_MS_BTN_MIDDLE		NC_MS_BTN_2
// ========</device_codes_nc>========

// ========<event_types_nc>========
#define NC_RELEASE				0
#define NC_PRESS				1

#define NC_MS_PRESS_LEFT		0x0001
#define NC_MS_PRESS_RIGHT		0x0002
#define NC_MS_PRESS_2			0x0004
#define NC_MS_PRESS_3			0x0008
#define NC_MS_PRESS_4			0x0010

#define NC_MS_PRESS_DOUBLE		0x0002

#define NC_MS_MOVED				0x0001
#define NC_MS_WHEELED			0x0004
#define NC_MS_HWHEELED			0x0008

#define NC_KEY_EVT				0x0001
#define NC_MS_EVT				0x0002
#define NC_WND_SIZE_EVT			0x0004
#define NC_MENU_EVT				0x0008
#define NC_FOCUS_EVT			0x0010
// ========</event_types_nc>========

#define CONSOLE_NO_SELECTION            0x0000
#define CONSOLE_SELECTION_IN_PROGRESS   0x0001   // selection has begun
#define CONSOLE_SELECTION_NOT_EMPTY     0x0002   // non-null select rectangle
#define CONSOLE_MOUSE_SELECTION         0x0004   // selecting with mouse
#define CONSOLE_MOUSE_DOWN              0x0008   // mouse is down

#endif	// NC_DEF_HPP