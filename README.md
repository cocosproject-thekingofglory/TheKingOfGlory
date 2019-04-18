# The King Of Glory
---
## 项目规范
### Git使用注意事项
 
  1.master分支用于发布稳定版本，develop分支用于开发版本，每项模块都已开发好，不可在develop上直接修改。
 
 2.队员将仓库clone到本地，开发新模块时，以develop为起点建立新的分支，分支命名为feature-模块名称，如：feature-GameStartScene.
 
 3.新模块开发完后,自己调试过没有问题后，在本地commit，注意写清commit的描述，再push到github上，发送pull request，由其他队员检查代码并调试，没有问题后，再将feature分支合并到develop分支，注意不要在本地将feature分支合并到develop分支上。
 
 4.及时pull，检查自己修改的版本是不是基于远程仓库上的最新版本.
 + 其他详细见[Git Flow工作流程](https://www.jianshu.com/p/9a76e9aa9534)
