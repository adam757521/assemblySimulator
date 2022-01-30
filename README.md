<h1 align="center">assemblySimulator</h1>

<p align="center">
  <a href="#"><img src="https://img.shields.io/codefactor/grade/github/adam757521/assemblySimulator?style=flat-square" /></a>
</p>

<p align="center">
   An assembly simulator that interprets assembly.
</p>

Disclaimer
-------------
This project is current work in progress and I am creating it in order to learn C (and have fun).
`If you like this project, please consider giving it a star! <3`

Examples
-------------
A traditional "Hello, World" program.
```asm
main:
mem string 13
mov string "Hello, World\n"

syscall 0 1 string 13
```

Note
-------------
Incase you have any suggestions, found any memory leaks/bugs or generally bad code, please create an issue or a PR.
