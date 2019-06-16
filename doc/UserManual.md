# The King Of Glory用户手册
***
[TOC]
***
## 游戏介绍
***
* **游戏规则**：
  * 摧毁敌方所有防御塔（包括商店），游戏即结束
  * 1V1 Mode:兵线只有中路
  * 5V5 Mode:兵线有上中下三路
* **英雄**
  * **属性**
    * HP
    * 经验：通过击杀敌方小兵、英雄和塔或野怪获得
    * 等级：达到一定经验值后升级，升级增加最大HP值、伤害值和防御力
    * 金钱：通过击败敌方英雄、小兵、防御塔、时间获得
    * 伤害值：普通攻击伤害值
    * 防御力：受到攻击时，减少的HP值为 对方伤害值X（1-防御力）
  * 普通攻击
  * 技能：每个英雄有两个固定的技能（加速和回复）以及三个特有的技能，有一定的缓冲时间
  * 类型：Warrior,Aviator,Mage，Paladin,Ranger,Cavalier
* **小兵**
  * 近战兵、炮车
  * 游戏开始后生成，数量固定
* **野怪**：
  * 红Buff、蓝Buff
  * 游戏开始后，每个一定时间刷新一次，英雄击杀能够获得经验、金钱，并短时间提高伤害值、防御力
* **防御塔**：
  * 攻击对方英雄、小兵，当一方所有防御塔都被摧毁时，游戏结束
* **基地**：英雄出生地、复活地，为己方英雄回血
* **装备**：
  * 为英雄增加相应的最大HP值、伤害值、防御力
  * 能够购买和出售
***
## 菜单界面
***
### 登录界面
* **在输入框中填入用户名，联网模式需用到，用户名不能与其他玩家相同**

![LoginScene](UserManual/LoginScene.png)
### 开始菜单界面

![StartScene](UserManual/StartScene.png)

* **Play** ：开始游戏
* **Setting** ：游戏音乐和音效设置
* **Help** ：游戏帮助
* **Exit** ：退出游戏

![SelectScene](UserManual/SelectScene.png)

#### Offline Mode ：单机模式
* **选择英雄**：
 ![SelectHero](UserManual/SelectHeroScene.png)
#### Online Mode ：联网模式
* **选择模式**： 
      ![SelectModeScene](UserManual/SelectModeScene.png)
      ![OnlineScene](UserManual/OnlineScene.png)
    * **Star As Server** ：作为服务器加入游戏
        ![Server](UserManual/ServerScene.png)
        * **Start Server** ：使用端口号启动服务器
        * **Start Game** :开始游戏
    * **Start As Client** ：作为客户端加入游戏
    ![Client](UserManual/ClientScene.png)
      * **Join Game**: 通过IP和端口号连接到服务器
    * **联网模式下，先启动一个应用程序作为服务器，作为服务器的应用程序自身带有一个客户端，其他的应用程序作为客户端加入游戏，IP地址要填服务器的IP地址，端口号要服务器的一致**
            ![Server](UserManual/StartServerScene.png)
     * **当下方显示的客户端连接个数大于一时，才能开始游戏**
      ![SelectHero](UserManual/SelectHeroScene.png)
     * **所有客户端都选择英雄后，游戏才会开始**
***
## 游戏界面
***
![GameScene](UserManual/GameScene.png)
* 玩家控制：
  * 鼠标左键单击：移动
  * A键：普通攻击
  * S键：加速技能
  * R键：回复技能
  * Q键：技能1
  * W键：技能2
  * E键：技能3
  * 点击相应的技能图标将释放相应技能
* 商店：点击商店会弹出商店界面
![Store](UserManual/Store.png)
  * 右上角是玩家当前的金钱数量
  * 点击相应的装备能够查看装备详细
  ![Equipment](UserManual/Equipment.png)
  * 在金钱足够的情况下，点击购买按钮能够购买相应的装备
  * (成为VIP将解锁隐藏装备!!!! >_<)
* 状态栏：点击右上角的状态栏图标能够查看玩家状态
![Status](UserManual/StatusList.png)
 * 点击出售按钮能够出售拥有的装备
 ![Sell](UserManual/Sell.png)
* 游戏设置：点击右上角的设置按钮
  ![Setting](UserManual/Setting.png)
* 聊天栏：联机模式下，与其他玩家聊天
![ChatBox](UserManual/ChatBox.png)
