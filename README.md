# 🐾 随机支线任务生成器 (Random Task Generator)

参考视频：https://www.bilibili.com/video/BV12JcXzVEm3/?spm_id_from=333.1007.tianma.1-2-2.click&vd_source=e021b85d0542fc742b76c4e97c13e02f

> “生活需要一点随机的火花，跳出舒适圈，去完成你的今日专属支线任务吧！”

这是一个基于 **C语言** 和 **GTK3** 图形库编写的轻量级 Linux 桌面应用程序。每天点击一次按钮，像素小猫就会为你随机派发一个生活/学习向的“支线任务”，并自动生成专属的 Markdown 任务打卡文档。

---

## ✨ 功能特性 (Features)

- 🎨 **二次元猛男粉 UI**：定制的 CSS 样式，粗体大字与粉色按钮，带来好心情。
- 🐱 **像素小猫陪伴**：内置可爱的 ASCII Art 简笔画小猫为你加油打气。
- 🎲 **精选任务库**：内置 10 种不同维度的挑战任务（夜间探索、身体技能、24h创作挑战、独处体验等）。
- 📝 **自动生成 Markdown 打卡文档**：
  - 点击生成后，会自动在程序所在目录创建 `Daily` 文件夹。
  - 按照 `YYYY-MM-DD.md` 的格式生成当天的任务档案。
  - 文档内已预设“任务内容”、“完成时间”和“完成感悟”栏目，方便后续记录。
- 🛡️ **每日限额防刷机制**：
  - 每天只能抽取一次任务！
  - 如果检测到今天已经生成过任务文档且未删除，再次点击会弹出原生 GTK 拦截警告：“**请完成今天任务数量已超标，明天再来喵~**”。

---

## 🛠️ 环境依赖 (Prerequisites)

本项目在 **Ubuntu / Debian** 环境下开发。由于使用了原生的 GTK3 图形库，在编译前需要安装相应的开发包。

打开终端，运行以下命令安装依赖：

```bash
sudo apt update
sudo apt install build-essential libgtk-3-dev pkg-config
```

---

## 🚀 编译与运行 (Build & Run)

请**不要**使用代码编辑器（如 VS Code）自带的默认“一键运行”按钮，这会导致缺少 GTK 链接库而报错。请在终端中手动执行以下命令：

### 1. 编译代码
在 `main.c` 所在的目录下，打开终端并运行：

```bash
gcc main.c -o task_generator $(pkg-config --cflags --libs gtk+-3.0)
```
*(编译成功后，当前目录下会生成一个名为 `task_generator` 的可执行文件。)*

### 2. 运行程序
```bash
./task_generator
```

---

## 📂 目录结构说明 (Directory Structure)

```text
RandomTaskGen/
├── main.c              # 核心 C 语言源代码 (UI逻辑、文件操作、防刷判定)
├── task_generator      # 编译后生成的可执行文件 (Linux)
├── README.md           # 项目说明文档
└── Daily/              # [程序自动生成] 每日任务打卡文件夹
    ├── 2023-10-25.md   # [程序自动生成] 当日生成的具体任务文档
    └── ...
```

---

## 💡 自定义修改 (Customization)

- **修改题库**：打开 `main.c`，找到顶部的 `const gchar* tasks[]` 数组，直接替换为你自己想挑战的任务即可。
- **修改UI颜色**：在代码底部的 CSS 字符串中，修改 `#FF69B4` (猛男粉) 或 `#FFB6C1` (浅粉色) 的色号。

---

**Have fun & Enjoy your life! 🐾**
