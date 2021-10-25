# Tubes Alstrukdat

## UML Diagram
![UML Diagram](assets/uml-diagram.png)

## How to run
- In windows
  ```
  powershell
  gci -Recurse -Include *.c -Name | % { gcc -c $_ } ; gcc *.o -o main ; rm -r *.o
  .\main.exe
  ```
- In Linux / bash
  ```sh
  gcc -o main ./src/*/*.c ./src/*/*/*.c
  ```