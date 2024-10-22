# QT6-lcnc-widget


This LinuxCNC 2.10.0 test (but it also works on 2.9.x and with 2.8.x) on Qt6 (v6.7.3), QtCreator 14, and LinuxMint 22 with rt-preempt 6.10 is intended for those who want to create something customized with LinuxCNC. Using QtPyVcp is certainly easier and supported... once you "learn" this way of interfacing with LinuxCNC and C++, you will be able to use all the features of QT6 with LinuxCNC... including buses not developed on LinuxCNC, such as OpcUa, CanOpen, EthernetIP, and anything else available online.

The creation of the interface requires you to have a .hal file and an .ini file... a ClassicLadder file is recommended. In this example, there are hal_cmd1, hal_cmd2, etc. To test, use the demo_sim_classicladder configuration available on LinuxCNC 2.10.0 and add your pins. You need to create in your .hal file all the signals you are interested in using -- pay attention to the names -- with bool or float values. With get_command.h you will read them all (if you need continuous readings, create specific functions), and with set_command.h you will be able to assign them a new value... you can create an RCS_CMD_CHANNEL, an RCS_ERROR_CHANNEL, or an RCS_STAT_CHANNEL... see the "motionlogger" application online and learn from there... this project is just an introduction.

ATTENTION ATTENTION... you must initialize your component first; read the files carefully... a distraction could cost you days. The terminal is not exhaustive in these matters. LinuxCNC requires thorough knowledge.

The WLED plugin referred to by the files WLED.ccp and WLED.h must be compiled, and the resulting library should be placed in the plugin folder of QtDesigner in your QT6 installation. The project folder is inside the repository: remove it and compile it separately with QtCreator.

Thanks to everyone who has taught me or from whom I have learned over time: arkEye, PCW, AndyPugh, db1981, and "the boss" grotius. Obviously, many others have suggested things over time that I missed, providing me support and helping me learn. I hope to do my part over time.

