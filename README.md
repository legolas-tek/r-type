<div align="center">
  <img src="https://www.dotemu.com/wp-content/uploads/2016/08/r_type_logo.png" alt="Logo">

  ![Static Badge](https://img.shields.io/badge/r--type-game_engine-blue)
  ![GitHub issues](https://img.shields.io/github/issues/legolas-tek/r-type)
  ![GitHub Workflow Status (with event)](https://img.shields.io/github/actions/workflow/status/legolas-tek/r-type/github-actions-compile.yml)
  ![GitHub Workflow Status (with event)](https://img.shields.io/github/actions/workflow/status/legolas-tek/r-type/github-actions-win64-compile.yml?label=windows%20build)
  ![GitHub top language](https://img.shields.io/github/languages/top/legolas-tek/r-type)

  <p>Here you will find an R-Type game, as well as a complete networking system, but mostly, a complete open-source game engine (ECS) 🎮</p>
</div>

<div align="left">

  <br/>

  <h1>PELAB's R-Type and Game Engine 🎮</h1>

  <p>This repository contains an open-source ECS developed in C++. This engine is completely modular and is waiting for your contribution. There's plenty of work to do concerning the other features of R-Type:</p>

  <ul>
    <li>The network protocol, like any other protocol, has room for improvement.</li>
    <li>The R-Type game implementation can always have more features added.</li>
    <li>Any other game could be developed using the ECS game engine.</li>
  </ul>

  <br/>

  <h2>Needed Dependencies ⚙️</h2>

  <p>This project will use various dependencies, some are basic, and others are more specific. You can install the specific ones with the following commands:</p>

  <h3>For Ubuntu:</h3>
  <pre><code>sudo apt install git cmake clang</code></pre>

  <h3>For Fedora:</h3>
  <pre><code>sudo dnf install git cmake clang</code></pre>

  <h3>For ArchLinux:</h3>
  <pre><code>sudo pacman install git cmake clang</code></pre>

  <h3>For macOS:</h3>
  <pre><code>brew install git cmake</code></pre>

  <br/>

  <h2>Build the Project 🛠️</h2>

  <p>After installing the necessary dependencies, in order to build the project, use CMake. Follow these steps:</p>

  <p>Clone the project:</p>
  <pre><code>git clone https://github.com/legolas-tek/r-type.git</code></pre>

  <p>Go to the project directory:</p>
  <pre><code>cd r-type</code></pre>

  <p>Build using CMake:</p>
  <pre><code>cmake -Bbuild -DCMAKE_BUILD_TYPE=Release</code></pre>

  <p>If you specifically want to build for your platform, use the right preset:</p>

  <h3>For Linux:</h3>
  <pre><code>cmake -Bbuild --preset linux-amd64 -DCMAKE_BUILD_TYPE=Debug -DDEBUG_NETWORK=1</code></pre>

  <h3>For Windows:</h3>
  <pre><code>cmake -Bbuild --preset x64-debug -DCMAKE_BUILD_TYPE=Debug</code></pre>

  <h3>For macOS:</h3>
  <pre><code>cmake -Bbuild --preset macos-arm64 -DCMAKE_BUILD_TYPE=Debug</code></pre>

  <h2>Then, you can finally build:</h2>
  <pre><code>cmake --build build</code></pre>

  <br/>

  <h2>Documentation 📖</h2>

  <p>In addition to the developer documentation, some other documentation is available on our GitHub Wiki:</p>

  <ul>
    <li><a href="https://github.com/legolas-tek/r-type/wiki/Lobby-Network-Protocol">Lobby Network Protocol</a></li>
    <li><a href="https://github.com/legolas-tek/r-type/wiki/Game-Network-Protocol">Game Network Protocol</a></li>
    <li><a href="https://github.com/legolas-tek/r-type/wiki/Systems-list">System List</a></li>
    <li><a href="https://github.com/legolas-tek/r-type/wiki/Component-list">Component List</a></li>
  </ul>

  <p>And more documentation is available on the Wiki.</p>

  <br/>

  <h2>Contributing 🤝</h2>

  <p>Contributions are always welcome! See <a href="https://github.com/legolas-tek/r-type/CONTRIBUTING">CONTRIBUTING</a> for ways to get started. Please adhere to this project's code of conduct.</p>
</div>
