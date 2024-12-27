
# SNEK compatibility list - SNEKCL
| Operating System | Architecture | Real Hardware | VM | Works? | 
| ---------------- |--------------| ------------- | -- | ------ |
|    Windows 95³    |      x86     |       :x:      | :x: | :x: |
|    Windows 98³    |      x86     |      :x:      |:white_check_mark:|:x:|
|  Windows NT 4.0  |      x86     |      :x:     |:white_check_mark:| :white_check_mark:⁴ |
| Windows 2000 RTM |      x86     |:x:|:white_check_mark:| :white_check_mark: |
| Windows 2000 SP4 |      x86     |:white_check_mark:|:white_check_mark:| :white_check_mark: |
|   Windows XP SP3 |      x86     |:white_check_mark:|:white_check_mark:| :white_check_mark: |
|   Windows 7 SP1  |   x86 & x64  |:white_check_mark:|:white_check_mark:| :white_check_mark:|
|   Windows 8 [.1] |      x86     |:white_check_mark: |:white_check_mark:| :white_check_mark:|
|   Windows 10     |   x86 & x64  |:white_check_mark:|:white_check_mark:| :white_check_mark:|
|   Windows 11     |      x64     |:white_check_mark:|:x:| :white_check_mark:|
|   ReactOS 0.4.14 |      x86     |      :x:      |:white_check_mark:| :white_check_mark:|
|Ubuntu [with Wine]|   x86 & x64  |:white_check_mark:|:white_check_mark:| :white_check_mark:|
| Microsoft Whistler 2419 | x86 | :white_check_mark: | :x: | :white_check_mark:|

*3. Windows 9X was tested back when SNEK v1.0.0.1 was released. Due to Packet reading not working in Win9X, versions above v1.0.0.2 and higher won't be compatible with it - Current Result shows testing the latest version*

*4. After downgrading the Freeglut library version to 2.6.0-3, which supports Windows NT 4.0*
