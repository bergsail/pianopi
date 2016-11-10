# pianopi
这是一个钢琴派智能钢琴原型的软件实现。在树莓派2Debian系统实施，使用qt5编译，前端使用qml实现,适合用于学习研究和diy。
jmidi文件夹为常用jdksmidi库，解析midi文件，辅助播放控制
keyboards文件夹实现键盘交互，包含rtmidi库，实现电钢midi信号传入传出
pianoroll文件夹实现音块瀑布流的动画显示
pp文件夹为中央控制模块，包含qml各种前端，视频播放POC组件也放在这个部分

This is software project of a smartpiano prototype named piano pie.It is realized on raspberrypi debian distribution,
builded by qt5, using qml and qualified of study and diy.
The folder jmidi using the well known jdksmidi, used to parse midi file, assist in play control.
The folder keyboards realize the interaction, including rtmidi,realize the signal transition for the electric piano.
The folder pianoroll realize the pianoroll animation.
The folder pp is the central control module, inluding the frontend display and videoplay POC component is also included here.

demo:  http://v.youku.com/v_show/id_XODk1NTcxMDA4.html?from=y1.7-2
project url: http://miumini.com/@autopiano （updating)
