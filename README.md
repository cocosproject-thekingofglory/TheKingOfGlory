# The King Of Glory（2D)
---
## 开发计划
### 基础功能
- [x] 1V1地图 
- [x] 三种英雄类型（Warrior,Aviator,Mage）
- [x] 英雄操作方式
- [x] 支持小兵、防御塔AI
- [x] 电脑AI
- [x] 三种基础小兵（近战兵、远程兵、炮车）
- [x] 支持经验、等级系统
- [x] 支持装备系统
- [x] 支持金钱的各种获取方式（补兵、防御塔、击败敌方英雄、时间）
- [x] 支持战绩、装备页面查看
- [x] 实现服务端：联机对战
### 进阶功能
- [ ] 5V5地图
- [x] 支持更多英雄(Paladin,Ranger,Cavalier)
- [ ] 支持三种野怪（红buff、蓝buff、暴君）
- [x] 支持聊天
### 类
+ Scene
   + LoadingScene:加载声音、动画等资源
   + LoginScene:登录界面
   + StartScene:开始界面：包含开始游戏、游戏设置、游戏帮助、退出游戏按钮
   + SettingsScene:游戏设置：背景音乐、音效音量大小设置
   + HelpScene:游戏帮助：游戏操作方式
   + SelectScene:选择英雄界面
   + GameScene:游戏场景   
+ Manager
   + PlayerManager:英雄管理类
   + SoldierManager:小兵管理类
   + TowerManager:防御塔管理类
   + EquipManager:装备管理类
   + MoneyManager:金钱管理类
+ Controller
   + GameController:游戏控制：控制游戏流程，判断游戏是否结束
+ Model
   + GameMap:游戏地图
   + User:用户信息
   + Player:英雄
   + Soldier:小兵
   + Tower:防御塔
   + Equip:装备
+ Util
   + GameAudio:游戏音乐：音乐、音效的播放、停止
   + Animations:游戏动画:动画获取、播放、停止
+ Network
---   
## 项目规范
### 游戏开发
### Git使用注意事项
 
  1.master分支用于发布稳定版本，develop分支用于开发版本，每项模块都已开发好，不可在develop上直接修改。
 
 2.队员将仓库clone到本地，开发新模块时，以develop为起点建立新的分支，分支命名为feature-模块名称，如：feature-StartScene.
 
 3.新模块开发完后,自己调试过没有问题后，在本地commit，注意写清commit的描述，再push到github上，发送pull request，由其他队员检查代码并调试，没有问题后，再将feature分支合并到develop分支，注意不要在本地将feature分支合并到develop分支上。
 
 4.及时pull，检查自己修改的版本是不是基于远程仓库上的最新版本.
 + 其他详细见[Git Flow工作流程](https://www.jianshu.com/p/9a76e9aa9534)
### 命名规范
+ class以大写开头，大写分割单词，比如Bubbles, OpenScene

+ private变量小写，以_分割，例如my_private_var

+ public小写，以_分割，例如my_public

+ 函数尽量用[驼峰命名法](https://blog.csdn.net/weibo1230123/article/details/82829537)
