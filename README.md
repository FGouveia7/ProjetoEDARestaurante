# Projeto — Simulação de Restaurante (CLI)

Este repositório contém uma **simulação textual (CLI)** em **C++**, onde podes acompanhar e gerir o estado de um restaurante: **mesas**, **fila de entrada** e **balcão**. O programa imprime o estado inicial e permite avançar ciclos/ações através de menus no terminal.

O ponto de entrada do programa é `Main/1main.cpp` (função `main`), que inicializa `Balcao`, carrega nomes, cria as mesas e a fila inicial, e entra no loop de menus (`menu_s` / `menu_o`).

## Funcionalidades

- **Estado do restaurante**: impressão do estado atual (mesas, fila, balcão).
- **Mesas**: criação e inicialização dinâmica de um número variável de mesas.
- **Clientes e fila**: geração de clientes e gestão da fila de entrada.
- **Balcão**: inicialização e gestão de clientes no balcão.
- **Menus de interação**: opções no terminal para avançar (“Seguinte”) e aceder a operações (“Opções”).

## Tecnologias utilizadas

- **C++20** (aplicação de consola)
- **CMake** (build)

## Requisitos

- **CMake 3.30+** (conforme `Main/CMakeLists.txt`)
- **Compilador com suporte a C++20** (ex.: MSVC / MinGW / clang)

Para confirmar:

```bash
cmake --version
```

## Instalação

1. **Clonar o repositório**:

```bash
git clone https://github.com/FGouveia7/ProjetoEDARestaurante
```

2. **Entrar na pasta do projeto**:

```bash
cd <folder onde tem o clone do repo>
```

## Compilar e executar (CMake)

O `CMakeLists.txt` está em `Main/`, portanto os comandos abaixo usam esse diretório como source.

### Windows (PowerShell)

```bash
cmake -S .\Main -B .\build
cmake --build .\build --config Debug
.\build\Debug\Projeto.exe
```

Se o teu gerador não criar a pasta `Debug\` (ex.: Ninja/MinGW), o executável pode ficar diretamente em `.\build\Projeto.exe`:

```bash
.\build\Projeto.exe
```

### Linux/macOS (opcional)

```bash
cmake -S ./Main -B ./build
cmake --build ./build
./build/Projeto
```

## Utilização (no terminal)

Ao iniciar, o programa mostra:

- o **estado inicial do restaurante**
- um prompt para escolher uma opção:
  - **`s`**: Seguinte
  - **`o`**: Opções

Exemplo:

```text
Escolha uma opcao: (s) Seguinte, (o) Opcoes:
```

## Estrutura do projeto

- `README.md`: este ficheiro
- `Main/CMakeLists.txt`: build CMake (cria o executável `Projeto`)
- `Main/1main.cpp`: ponto de entrada (loop principal e menus)
- `Main/2estruturas.h`: structs principais (`cliente`, `Mesa`, `Balcao`)
- `Main/3cliente.*`: lógica de clientes
- `Main/4fila.*`: lógica de fila
- `Main/5mesa.*`: lógica de mesas
- `Main/6balcao.*`: lógica de balcão
- `Main/7Menus.*`: menus/ações (interface de interação)
- `Main/8carregarEguardar.*`: carregar/guardar (persistência)

## Problemas comuns

- **CMake não encontra compilador**: no Windows, instala “Desktop development with C++” (Visual Studio) ou configura MinGW/clang, e volta a correr `cmake -S ... -B ...`.
- **Pasta `cmake-build-debug/` aparece no git status**: é uma pasta de build gerada pelo IDE/CMake e **não deve ser commitada**.

## Contribuição

Sugestões e melhorias são bem-vindas:

- abrir **issues** para bugs/ideias
- criar **pull requests** com melhorias (ex.: novas opções de menu, regras de simulação, persistência)

## Licença

Projeto para fins educacionais. Sem licença específica definida.