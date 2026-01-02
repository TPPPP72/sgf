# SGF

一个轻量级C++游戏开发框架，目前提供了完整的2D图形渲染基础设施。

## 项目状态

**⚠️ 注意**: 目前仅实现了基础的图形渲染模块，游戏框架的其他部分（如音频、输入、物理等）将在后续版本中逐步添加。

## 特性

### ✅ 已实现
- 🎯 **窗口管理**: 创建、配置和管理游戏窗口
- 🖼️ **渲染管线**: 完整的2D渲染流程
- 🔤 **字体渲染**: TTF字体支持和文本渲染
- 🖌️ **纹理系统**: 图像加载、文本纹理、动态纹理创建
- 🌈 **颜色系统**: RGBA颜色支持
- 📐 **几何图形**: 矩形绘制和操作

### 🔄 计划中
- 🎮 输入系统（键盘、鼠标、手柄）
- 🔊 音频系统
- ⚡ 物理引擎集成
- 📦 资源管理器
- 🎬 动画系统
- 📊 UI系统

## 快速开始

### 环境要求
- C++17 或更高
- CMake 3.25+
- Harfbuzz

### 安装依赖

#### Windows (msys2)
```bash
pacman -S mingw-w64-ucrt-x86_64-harfbuzz
```

### 最小示例

```cpp
#include <sgf/base/renderer.hpp>
#include <sgf/base/texture.hpp>
#include <sgf/base/window/window.hpp>

using namespace sgf;

int main()
{
    // 1. 创建游戏窗口
    base::window_info game_window_info{
        .title = "My First Game",
        .width = 800,
        .height = 600
    };
    
    base::window game_window{game_window_info};
    
    // 2. 创建渲染器
    base::renderer game_renderer{game_window};
    
    // 3. 加载游戏字体
    base::font game_font{"assets/fonts/game_font.ttf", 24};
    
    // 4. 创建游戏对象纹理
    base::texture player_texture{game_renderer, "assets/images/player.png"};
    base::texture score_text{game_renderer, game_font, 
                             "Score: 0", 
                             {255, 255, 255, 255}};
    
    // 5. 游戏主循环
    bool is_running = true;
    while (is_running)
    {
        // 处理窗口事件
        game_window.poll_event();
        
        // 开始渲染帧
        game_renderer.clear();
        
        // 渲染游戏对象
        game_renderer.render_texture(player_texture, 100, 100);
        game_renderer.render_texture(score_text, 20, 20);
        
        // 绘制UI元素
        type::rect health_bar{20, 550, 200, 20};
        game_renderer.set_draw_color({255, 0, 0, 255});
        game_renderer.render_rect(health_bar);
        
        // 结束渲染帧
        game_renderer.present();
    }
}
```

## API 文档

### 核心模块

#### 窗口系统 (`window.hpp`)
```cpp
// 窗口配置
struct window_info {
    std::string   title;   // 窗口标题
    uint32_t      width;   // 窗口宽度
    uint32_t      height;  // 窗口高度
};

class window {
public:
    explicit window(const window_info& info);
    void poll_event();  // 轮询窗口事件
    void set_fullscreen(bool enable);  // 全屏切换
    std::tuple<uint32_t, uint32_t> current_size() const;  // 获取窗口尺寸
};
```

#### 渲染器 (`renderer.hpp`)
```cpp
class renderer {
public:
    explicit renderer(const window& target_window);
    
    // 渲染控制
    void clear();  // 清空渲染目标
    void present();  // 呈现渲染结果
    
    // 绘制操作
    void set_draw_color(const type::color& color);
    void render_texture(const texture& tex, double x, double y);
    void render_rect(const type::rect& rect);
    void render_rect(const type::rect& rect, const type::color& color);
};
```

#### 纹理系统 (`texture.hpp`)
```cpp
class texture {
public:
    // 从文件创建
    texture(const renderer& rdr, const std::filesystem::path& image_path);
    
    // 从文本创建
    texture(const renderer& rdr, const font& fnt, 
            const std::string& text, const type::color& color);
    
    // 创建空白纹理
    texture(const renderer& rdr, uint32_t width, uint32_t height);
    
    // 获取尺寸
    std::tuple<double, double> size() const;
};
```

#### 字体系统 (`font.hpp`)
```cpp
class font {
public:
    // 加载TTF字体
    font(const std::filesystem::path& font_path, uint32_t size);
};
```

### 数据类型

#### 颜色 (`color.hpp`)
```cpp
struct color {
    uint8_t r = 0;  // 红色分量 (0-255)
    uint8_t g = 0;  // 绿色分量 (0-255)
    uint8_t b = 0;  // 蓝色分量 (0-255)
    uint8_t a = 0; // 透明度 (0-255, 0=全透明)
};

// 常用颜色预定义
inline constexpr color RED{255, 0, 0, 255};
inline constexpr color GREEN{0, 255, 0, 255};
inline constexpr color BLUE{0, 0, 255, 255};
inline constexpr color WHITE{255, 255, 255, 255};
inline constexpr color BLACK{0, 0, 0, 255};
```

#### 矩形 (`rect.hpp`)
```cpp
struct rect {
    double x = 0;  // X坐标
    double y = 0;  // Y坐标
    double w = 0;  // 宽度
    double h = 0;  // 高度
};
```

## 构建指南

### 使用 CMake

```bash
# 克隆项目
git clone https://github.com/yourusername/sgf.git
cd sgf

# 创建构建目录
mkdir build && cd build

# 配置项目
cmake .. -DCMAKE_BUILD_TYPE=Release

# 编译
cmake --build . --config Release
```

<!-- ### 作为子模块使用

```cmake
# 在你的 CMakeLists.txt 中
add_subdirectory(sgf)
target_link_libraries(your_target PRIVATE sgf::sgf)
``` -->

## 开发计划

### v0.1.0 (当前版本)
- ✅ 基础窗口系统
- ✅ 2D渲染管线
- ✅ 纹理和字体支持
- ✅ 基本几何图形绘制

### v0.2.0 (计划中)
- 🎮 输入系统（键盘、鼠标）
- 🔊 基础音频播放
- 📦 资源加载器
- 📖 更完善的文档

### v0.3.0 (规划中)
- ⚡ 简单物理系统
- 🎬 精灵动画
- 📊 基础UI组件
- 🔧 场景管理

## 贡献指南

我们欢迎各种形式的贡献！

### 开发流程
1. Fork 项目仓库
2. 创建特性分支 (`git checkout -b feature/AmazingFeature`)
3. 提交更改 (`git commit -m 'Add some AmazingFeature'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 开启 Pull Request

<!-- ## 许可证

本项目采用 MIT 许可证 - 查看 [LICENSE](LICENSE) 文件了解详情。 -->

## 支持

- 🐛 [问题跟踪](https://github.com/TPPPP72/sgf/issues)
- 💬 [讨论区](https://github.com/TPPPP72/sgf/discussions)
- 📧 邮箱支持: support@example.com

## 致谢

感谢所有为这个项目做出贡献的开发者！

---
**Simple Game Framework** - 让游戏开发更简单

*注意：本项目仍在积极开发中，API可能会有变动。*