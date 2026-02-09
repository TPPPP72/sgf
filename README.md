# SGF

一个轻量级C++游戏开发框架，目前提供了完整的2D图形渲染、音频播放、输入系统和动画基础设施。

## 项目状态

**🚧 开发中**: 目前已完成核心模块的实现，包括图形渲染、音频系统、输入处理和动画播放，游戏框架的基础设施已经完善。

## 特性

### ✅ 已实现
- 🎯 **窗口管理**: 创建、配置和管理游戏窗口，支持全屏切换
- 🖼️ **渲染管线**: 完整的2D渲染流程，支持视口和坐标转换
- 🔤 **字体渲染**: TTF字体支持和文本渲染
- 🖌️ **纹理系统**: 图像加载、文本纹理、动态纹理创建
- 🌈 **颜色系统**: RGBA颜色支持
- 📐 **几何图形**: 矩形绘制和操作
- 🎮 **输入系统**: 完整的键盘与鼠标事件处理（按下、按住、释放状态）
- 🔊 **音频系统**: 支持音频加载、混音器和音轨管理
- 🎬 **动画系统**: 精灵动画剪辑和播放器，支持循环播放和帧控制
- 📦 **资源管理**: 统一的资源加载器，支持纹理、音频、字体和精灵图集

### 🔄 计划中
- ⚡ 物理引擎集成
- 📊 UI系统
- 🔧 更高级的动画状态机
- 🎯 粒子系统

## 快速开始

### 环境要求
- C++17 或更高
- CMake 3.25+
- SDL3 及相关扩展库（SDL_image, SDL_ttf, SDL_mixer）

### 安装依赖

#### Linux
以下来自于 `SDL3` 官方文档

对于 `Ubuntu 18.04`，你需要执行：
```bash
sudo apt-get install build-essential git make \
pkg-config cmake ninja-build gnome-desktop-testing libasound2-dev libpulse-dev \
libaudio-dev libfribidi-dev libjack-dev libsndio-dev libx11-dev libxext-dev \
libxrandr-dev libxcursor-dev libxfixes-dev libxi-dev libxss-dev libxtst-dev \
libxkbcommon-dev libdrm-dev libgbm-dev libgl1-mesa-dev libgles2-mesa-dev \
libegl1-mesa-dev libdbus-1-dev libibus-1.0-dev libudev-dev libthai-dev libharfbuzz-dev
```
对于 `Ubuntu 22.04+`，你需要额外执行：
```bash
sudo apt-get install libpipewire-0.3-dev libwayland-dev libdecor-0-dev liburing-dev
```

#### Windows
如果你使用 `MSVC` 编译器，不需要进行任何额外的环境配置操作  
如果你使用其他编译器，应至少编译安装 `harfbuzz` 库

#### MacOS
```bash
brew install cmake harfbuzz freetype pkg-config
```

### 编译配置
强制使用子模块源码构建，请开启
```cmake
-DSDLIMAGE_VENDORED=ON -DSDLTTF_VENDORED=ON -DSDLMIXER_VENDORED=ON
```

### 最小示例

```cpp
#include <sgf/kernel.hpp>
#include <sgf/resources/manager.hpp>
#include <sgf/animation/player.hpp>
#include <sgf/input_system.hpp>

using namespace sgf;

class MyGame : public kernel<MyGame>
{
public:
    MyGame()
        : kernel("My Game", {800, 600}, 60),
          res_mgr(get_renderer()),
          player_anim()
    {
        // 加载资源（返回引用）
        player_texture = &res_mgr.load_texture("assets/player.png");
        game_font = &res_mgr.load_font("assets/font.ttf", 24);
        
        // 创建精灵图集
        resources::atlas_directory_info atlas_info{
            .root_path = "assets/player_anim",
            .name = "player_run",
            .number = 8,
            .extension = ".png"
        };
        
        // 加载图集（返回引用）
        player_atlas = &res_mgr.load_atlas_from_directory(atlas_info);
        
        // 创建动画剪辑
        player_clip.frames.clear();
        // 获取图集中的所有精灵
        for (int i = 0; i < 8; ++i) {
            std::string frame_name = "player_run_" + std::to_string(i);
            player_clip.frames.push_back(&player_atlas->get(frame_name));
        }
        player_clip.frame_duration = std::chrono::milliseconds(100);
        player_clip.loop = true;
        
        // 开始播放动画
        player_anim.play(&player_clip);
    }
    
    void on_update(kernel<MyGame>& k, std::chrono::nanoseconds dt)
    {
        input_system& input = input_system::instance();
        
        // 处理输入
        if (input.is_key_down(base::key_code::w))
            player_y -= 100.0 * dt.count() / 1e9;
        if (input.is_key_down(base::key_code::s))
            player_y += 100.0 * dt.count() / 1e9;
        if (input.is_key_down(base::key_code::a))
            player_x -= 100.0 * dt.count() / 1e9;
        if (input.is_key_down(base::key_code::d))
            player_x += 100.0 * dt.count() / 1e9;
            
        // 更新动画
        player_anim.update(dt);
        
        // 检查鼠标输入
        if (input.is_button_pressed(base::mouse_button_code::left)) {
            // 鼠标左键按下
            auto mouse_pos = input.get_mouse_position();
            // 将窗口坐标转换为视口坐标
            auto viewport = k.get_renderer().get_viewport(); // 假设有这个方法
            // 或者需要通过其他方式获取视口
        }
        
        k.get_window().set_title("My Game | FPS: " + std::to_string(k.get_current_fps()));
    }
    
    void on_render(kernel<MyGame>& k)
    {
        auto& rd = k.get_renderer();
        
        // 渲染玩家精灵（使用动画当前帧）
        const auto& current_sprite = player_anim.current_sprite();
        
        graphics::render(rd, current_sprite, 
                         type::view_rect{player_x, player_y, 64, 64});
        
        // 渲染UI文本
        auto score_text = base::texture(rd, *game_font, 
                                       "Score: 1000", 
                                       type::color::white);
        rd.render_texture(score_text, type::view_position{20, 20});
        
        // 渲染其他游戏元素...
    }
    
private:
    resources::manager res_mgr;
    const base::texture* player_texture;
    const base::font* game_font;
    const resources::atlas* player_atlas;
    
    animation::clip player_clip;
    animation::player player_anim;
    
    double player_x = 300;
    double player_y = 250;
};

int main()
{
    MyGame game;
    game.run();
    return 0;
}
```

## API 文档

### 核心模块

#### 游戏内核 (`kernel.hpp`)
```cpp
template<typename Game>
class kernel {
public:
    // 创建带FPS限制的窗口
    kernel(const std::string& title, const type::world_size& size, uint32_t max_fps);
    
    // 创建带垂直同步的窗口
    kernel(const std::string& title, const type::world_size& size);
    
    // 运行游戏循环
    void run();
    
    // 获取核心组件
    base::window& get_window() noexcept;
    base::renderer& get_renderer() noexcept;
    uint32_t get_current_fps() const noexcept;
};
```

#### 输入系统 (`input_system.hpp`)
```cpp
class input_system {
public:
    static input_system& instance() noexcept;
    
    // 绑定窗口
    void bind(base::window* window) noexcept;
    
    // 更新输入状态
    void update();
    
    // 键盘状态查询
    bool is_key_pressed(base::key_code key) const;
    bool is_key_down(base::key_code key) const;
    bool is_key_released(base::key_code key) const;
    
    // 鼠标状态查询
    bool is_button_pressed(base::mouse_button_code button) const;
    bool is_button_down(base::mouse_button_code button) const;
    bool is_button_released(base::mouse_button_code button) const;
    
    // 获取鼠标位置
    type::window_position get_mouse_position() const;
};
```

#### 动画系统 (`clip.hpp`, `player.hpp`)
```cpp
// 动画剪辑
struct clip {
    std::vector<const resources::sprite*> frames;  // 帧序列
    std::chrono::nanoseconds frame_duration;       // 每帧持续时间
    bool loop = true;                              // 是否循环播放
};

// 动画播放器
class player {
public:
    // 播放动画剪辑
    void play(const clip* clip);
    
    // 更新动画状态
    void update(std::chrono::nanoseconds dt);
    
    // 获取当前帧精灵
    const resources::sprite& current_sprite() const;
};
```

#### 音频系统 (`audio.hpp`, `mixer.hpp`, `track.hpp`)
```cpp
// 音频资源
class audio {
public:
    explicit audio(const std::filesystem::path& audio_file);
};

// 音频混音器
class mixer {
public:
    mixer();
};

// 音频轨道
class track {
public:
    enum class state {
        wait_for_audio,  // 等待绑定音频
        wait_for_play,   // 等待播放
        playing,         // 正在播放
        paused           // 已暂停
    };
    
    explicit track(const mixer& mixer);
    
    // 控制方法
    void bind_audio(const audio& audio);
    void play(bool is_loop);
    void pause();
    void resume();
    
    // 状态查询
    bool is_playing() const noexcept;
    bool is_paused() const noexcept;
    state get_state() const noexcept;
};
```

#### 资源管理器 (`manager.hpp`)
```cpp
class manager {
public:
    manager(base::renderer& renderer);
    
    // 资源加载方法
    const base::audio& load_audio(const std::filesystem::path& path);
    const base::font& load_font(const std::filesystem::path& path, uint32_t size);
    const base::texture& load_texture(const std::filesystem::path& path);
    const sprite& load_sprite(const std::filesystem::path& path);
    
    // 精灵图集加载
    const atlas& load_atlas_from_directory(const atlas_directory_info& info);
    const atlas& load_atlas_from_sheet(const atlas_sheet_info& info);
};
```

### 数据类型

#### 坐标系统
```cpp
using window_position = tagged_vec2<base::window_tag>;  // 窗口坐标
using view_position   = tagged_vec2<base::view_tag>;    // 视口坐标
using world_position  = tagged_vec2<base::world_tag>;   // 世界坐标

using window_size   = size<base::window_tag>;    // 窗口尺寸
using view_size     = size<base::view_tag>;      // 视口尺寸
using world_size    = size<base::world_tag>;     // 世界尺寸

using window_rect   = rect<base::window_tag>;    // 窗口矩形
using view_rect     = rect<base::view_tag>;      // 视口矩形
using world_rect    = rect<base::world_tag>;     // 世界矩形
```

#### 颜色 (`color.hpp`)
```cpp
struct color {
    uint8_t r = 0;  // 红色分量 (0-255)
    uint8_t g = 0;  // 绿色分量 (0-255)
    uint8_t b = 0;  // 蓝色分量 (0-255)
    uint8_t a = 0;  // 透明度 (0-255, 0=全透明)
};

// 常用颜色预定义
inline constexpr color red{255, 0, 0, 255};
inline constexpr color green{0, 255, 0, 255};
inline constexpr color blue{0, 0, 255, 255};
inline constexpr color white{255, 255, 255, 255};
inline constexpr color black{0, 0, 0, 255};
```

## 构建指南

### 使用 CMake

```bash
# 克隆项目
git clone https://github.com/TPPPP72/sgf.git
cd sgf

# 初始化子模块
git submodule update --init --recursive

# 创建构建目录
mkdir build && cd build

# 配置项目
cmake .. -DCMAKE_BUILD_TYPE=Release \
         -DSDLIMAGE_VENDORED=ON \
         -DSDLTTF_VENDORED=ON \
         -DSDLMIXER_VENDORED=ON

# 编译
cmake --build . --config Release
```

### 作为子模块使用

```cmake
# 在你的 CMakeLists.txt 中
add_subdirectory(sgf)
target_link_libraries(your_target PRIVATE sgf::sgf)
```

## 开发计划

### v0.1.0 (已完成)
- ✅ 基础窗口系统
- ✅ 2D渲染管线
- ✅ 纹理和字体支持
- ✅ 基本几何图形绘制

### v0.2.0 (已完成)
- ✅ 输入系统（键盘、鼠标）
- ✅ 音频系统（加载、播放、混音）
- ✅ 资源管理器
- ✅ 动画系统（剪辑、播放器）

### v0.3.0 (开发中)
- 🚧 物理系统集成
- 🚧 UI组件系统
- 🚧 高级动画状态机
- 🚧 粒子效果系统

## 贡献指南

我们欢迎各种形式的贡献！

### 开发流程
1. Fork 项目仓库
2. 创建特性分支 (`git checkout -b feature/AmazingFeature`)
3. 提交更改 (`git commit -m 'Add some AmazingFeature'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 开启 Pull Request

### 代码规范
- 遵循 C++ Core Guidelines
- 使用有意义的命名
- 添加必要的注释和文档
- 编写单元测试

## 许可证

本项目采用 MIT 许可证 - 查看 [LICENSE](LICENSE) 文件了解详情。

## 支持

- 🐛 [问题跟踪](https://github.com/TPPPP72/sgf/issues)
- 💬 [讨论区](https://github.com/TPPPP72/sgf/discussions)

## 致谢

感谢所有为这个项目做出贡献的开发者！  
特别感谢 SDL3 团队提供的强大跨平台多媒体库。

---
**Simple Game Framework** - 让2D游戏开发更简单

*注意：本项目仍在积极开发中，API可能会有变动。建议在生产环境中使用时锁定具体版本。*