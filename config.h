/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int gappih    = 8;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 8;       /* vert inner gap between windows */
static const unsigned int gappoh    = 8;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 8;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int vertpad            = 8;       /* vertical padding of bar */
static const int sidepad            = 8;       /* horizontal padding of bar */
static const char *fonts[]          = { "monospace:size=14" };
static const char dmenufont[]       = "monospace:size=14";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class,                   instance,   title,          tags mask,   isfloating, isterminal, noswallow, monitor */
	{ "libreoffice",            NULL,       NULL,           1<<1,        0,          0,          0,         -1       },
	{ "jetbrains-pycharm",      NULL,       NULL,           1<<3,        0,          0,          0,         -1       },
	{ "jetbrains-idea",         NULL,       NULL,           1<<3,        0,          0,          0,         -1       },
	{ "jetbrains-webstorm",     NULL,       NULL,           1<<3,        0,          0,          0,         -1       },
    { "St",                     NULL,       NULL,           0,           0,          1,          -1,        -1       },
	{ "St",                     NULL,       "neomutt",      1<<4,        0,          1,          -1,        -1       },
	{ "St",                     NULL,       "weechat",      1<<5,        0,          1,          -1,        -1       },
	{ "St",                     NULL,       "spt",          1<<6,        0,          1,          -1,        -1       },
	{ "St",                     NULL,       "calcurse",     1<<7,        0,          1,          -1,        -1       },
	{ "St",                     NULL,       "newsboat",     1<<8,        0,          1,          -1,        -1       },
	{ "zoom",                   NULL,       NULL,           0,           1,          0,          0,         -1       },
    { NULL,                     NULL,       "Event Tester", 0,           1,          0,          1,         -1       },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "|M|",      centeredmaster },
 	{ "[@]",      spiral },
 	{ "[\\]",     dwindle },
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD,	XK_j,	ACTION##stack,	{.i = INC(+1) } }, \
	{ MOD,	XK_k,	ACTION##stack,	{.i = INC(-1) } }, \

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-l", "25", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

#include <X11/XF86keysym.h>
#include "shiftview.c"
static Key keys[] = {
	/* modifier, key, function, argument */
	STACKKEYS(MODKEY, focus)
	STACKKEYS(MODKEY|ShiftMask, push)

	TAGKEYS(XK_1, 0)
	TAGKEYS(XK_2, 1)
	TAGKEYS(XK_3, 2)
	TAGKEYS(XK_4, 3)
	TAGKEYS(XK_5, 4)
	TAGKEYS(XK_6, 5)
	TAGKEYS(XK_7, 6)
	TAGKEYS(XK_8, 7)
	TAGKEYS(XK_9, 8)

	{ MODKEY,               XK_q,                       killclient,     {0}                                                                         },

	{ MODKEY,               XK_x,                       spawn,          SHCMD("poweropts")                                                          },
	{ MODKEY|ShiftMask,     XK_x,                       spawn,          SHCMD("poweropts lock")                                                     },
	{ MODKEY,			    XK_a,                       spawn,          SHCMD("st -e pulsemixer ; pkill -RTMIN+10 dwmblocks")                       },
    { MODKEY|ShiftMask,	    XK_s,                       spawn,          SHCMD("st -e spt -t 50")                                                    },
	{ 0,	                XF86XK_AudioPlay,           spawn,          SHCMD("playerctl --player=spotifyd play-pause")                             },
	{ 0,	                XF86XK_AudioNext,           spawn,          SHCMD("playerctl --player=spotifyd next")                                   },
	{ 0,	                XF86XK_AudioPrev,           spawn,          SHCMD("playerctl --player=spotifyd previous")                               },
	{ 0,	                XF86XK_AudioMute,           spawn,          SHCMD("pulsemixer --toggle-mute; pkill -RTMIN+10 dwmblocks")                },
	{ 0,	                XF86XK_AudioLowerVolume,    spawn,          SHCMD("pulsemixer --change-volume -5; pkill -RTMIN+10 dwmblocks")           },
	{ 0,	                XF86XK_AudioRaiseVolume,    spawn,          SHCMD("pulsemixer --change-volume +5; pkill -RTMIN+10 dwmblocks")           },
	{ 0,	                XF86XK_Tools,               spawn,          SHCMD("kbdbrightness")                                                      },
	{ 0,	                XF86XK_MonBrightnessUp,     spawn,          SHCMD("brightness up")                                                      },
	{ 0,	                XF86XK_MonBrightnessDown,   spawn,          SHCMD("brightness down")                                                    },

	{ MODKEY,               XK_Return,                  spawn,          {.v = termcmd }                                                             },
	{ MODKEY|ShiftMask,     XK_Return,                  togglescratch,  {.v = scratchpadcmd }                                                       },
	{ MODKEY,               XK_d,                       spawn,          {.v = dmenucmd }                                                            },
	{ MODKEY,               XK_w,                       spawn,          SHCMD("$BROWSER")                                                           },
	{ MODKEY,               XK_r,                       spawn,          SHCMD("st -e $FILE")                                                        },
	{ MODKEY,               XK_grave,                   spawn,          SHCMD("dmenuunicode")                                                       },
	{ MODKEY,               XK_p,                       spawn,          SHCMD("bwhelper")                                                           },
	{ MODKEY|ShiftMask,     XK_p,                       spawn,          SHCMD("present")                                                            },
	{ MODKEY|ShiftMask,     XK_g,                       spawn,          SHCMD("st -e gotop")                                                        },
	{ MODKEY|ShiftMask,     XK_w,                       spawn,          SHCMD("st -e sudo nmtui")                                                   },
	{ MODKEY,               XK_m,                       spawn,          SHCMD("st -e neomutt")                                                      },
	{ MODKEY|ShiftMask,     XK_m,                       spawn,          SHCMD("st -e weechat")                                                      },
	{ MODKEY,               XK_c,                       spawn,          SHCMD("st -e calcurse")                                                     },
	{ MODKEY|ShiftMask,     XK_c,                       spawn,          SHCMD("addtodo")                                                            },
	{ MODKEY,               XK_n,                       spawn,          SHCMD("st -e newsboat")                                                     },

	{ MODKEY,               XK_Insert,                  spawn,          SHCMD("showclip")                                                           },
	{ MODKEY,               XK_F1,                      spawn,          SHCMD("groff -mom $HOME/.local/share/larbs/readme.mom -Tpdf | zathura -")   },
	{ MODKEY,               XK_F2,                      quit,           {0}                                                                         },
	{ MODKEY,               XK_F3,                      spawn,          SHCMD("displaytoggle")                                                      },
	{ MODKEY,               XK_F5,                      xrdb,           {.v = NULL }                                                                },
	{ MODKEY,               XK_F6,                      spawn,          SHCMD("torwrap")                                                            },
	{ MODKEY,               XK_F7,                      spawn,          SHCMD("td-toggle")                                                          },
	{ MODKEY,               XK_F8,                      spawn,          SHCMD("st -e sudo nmtui")                                                   },
	{ MODKEY,               XK_F9,                      spawn,          SHCMD("dmenumount")                                                         },
	{ MODKEY,               XK_F10,                     spawn,          SHCMD("dmenuumount")                                                        },
	{ MODKEY,               XK_space,                   zoom,           {0}                                                                         },

	{ ShiftMask,            XK_Print,                   spawn,          SHCMD("maimpick")                                                           },
	{ MODKEY,               XK_Print,                   spawn,          SHCMD("dmenurecord")                                                        },
	{ MODKEY|ShiftMask,     XK_Print,                   spawn,          SHCMD("dmenurecord kill")                                                   },
	{ MODKEY,               XK_Delete,                  spawn,          SHCMD("dmenurecord kill")                                                   },

	{ MODKEY,               XK_t,                       setlayout,      {.v = &layouts[0]} /* tile */                                               },
	{ MODKEY,               XK_y,                       setlayout,      {.v = &layouts[1]} /* centered master */                                    },
	{ MODKEY,               XK_u,                       setlayout,      {.v = &layouts[2]} /* spiral */                                             },
	{ MODKEY,               XK_i,                       setlayout,      {.v = &layouts[3]} /* dwindle */                                            },
	{ MODKEY|ShiftMask,     XK_space,                   togglefloating,	{0} },

	{ MODKEY,               XK_0,                       view,           {.ui = ~0 }                                                                 },
	{ MODKEY|ShiftMask,     XK_0,                       tag,            {.ui = ~0 }                                                                 },
	{ MODKEY,               XK_Tab,                     view,           {0}                                                                         },
	{ MODKEY,               XK_backslash,               view,           {0}                                                                         },

	{ MODKEY,               XK_f,                       togglefullscr,  {0}                                                                         },
	{ MODKEY,               XK_s,                       togglesticky,   {0}                                                                         },
	{ MODKEY,               XK_b,                       togglebar,      {0}                                                                         },
	{ MODKEY|ShiftMask,     XK_d,                       togglegaps,     {0}                                                                         },

	{ MODKEY|ShiftMask,     XK_h,                       shiftview,      { .i = -1 }                                                                 },
	{ MODKEY|ShiftMask,     XK_l,                       shiftview,      { .i = 1 }                                                                  },
	{ MODKEY,               XK_h,                       setmfact,       {.f = -0.05}                                                                },
	{ MODKEY,               XK_l,                       setmfact,       {.f = +0.05}                                                                },
	{ MODKEY,               XK_z,                       incrgaps,       {.i = +1 }                                                                  },
	{ MODKEY|ShiftMask,     XK_z,                       incrgaps,       {.i = -1 }                                                                  },
	{ MODKEY,               XK_o,                       incnmaster,     {.i = +1 }                                                                  },
	{ MODKEY|ShiftMask,     XK_o,                       incnmaster,     {.i = -1 }                                                                  },

	{ MODKEY,               XK_Page_Down,               focusmon,       {.i = -1 }                                                                  },
	{ MODKEY,               XK_Page_Up,                 focusmon,       {.i = +1 }                                                                  },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

void
setlayoutex(const Arg *arg)
{
	setlayout(&((Arg) { .v = &layouts[arg->i] }));
}

void
viewex(const Arg *arg)
{
	view(&((Arg) { .ui = 1 << arg->ui }));
}

void
viewall(const Arg *arg)
{
	view(&((Arg){.ui = ~0}));
}

void
toggleviewex(const Arg *arg)
{
	toggleview(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagex(const Arg *arg)
{
	tag(&((Arg) { .ui = 1 << arg->ui }));
}

void
toggletagex(const Arg *arg)
{
	toggletag(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagall(const Arg *arg)
{
	tag(&((Arg){.ui = ~0}));
}

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"` */
static Signal signals[] = {
	/* signum           function */
	{ "focusstack",     focusstack },
	{ "setmfact",       setmfact },
	{ "togglebar",      togglebar },
	{ "incnmaster",     incnmaster },
	{ "togglefloating", togglefloating },
	{ "focusmon",       focusmon },
	{ "tagmon",         tagmon },
	{ "zoom",           zoom },
	{ "view",           view },
	{ "viewall",        viewall },
	{ "viewex",         viewex },
	{ "toggleview",     view },
	{ "toggleviewex",   toggleviewex },
	{ "tag",            tag },
	{ "tagall",         tagall },
	{ "tagex",          tagex },
	{ "toggletag",      tag },
	{ "toggletagex",    toggletagex },
	{ "killclient",     killclient },
	{ "quit",           quit },
	{ "setlayout",      setlayout },
	{ "setlayoutex",    setlayoutex },
	{ "xrdb",		xrdb },
};
