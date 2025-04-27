# Quick start

## macOS

```bash
brew install raylib
git clone https://github.com/qiekn/sokomaths.git
cmake -B build && make -j$(nproc) -C build
./build/game
```

`compile_commands.json` for neovim lsp config:

```bash
cd path/to/your/project
ln -s build/compile_commands.json ./compile_commands.json
```
