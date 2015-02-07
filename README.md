# hash
Have Another SHell

This is a shell I worked on for a practical during my System Software and Compilers course.

It's not very sane (why would a shell be creating and writing to files...?), but that was the point of the practical.

That's also why things such as ```printf``` haven't been used - I wanted to practice with raw syscalls instead.

## Using

Hash supports the following commands:
- ```hashwrite <filename>```: Create an empty file called ```filename``` - just like touch.
- ```hashread <filename>```: Read from ```filename``` and print it to screen.
- ```e <path to binary>```: Execute the binary at ```path to binary```.

## Example usage

```hashwrite test.c```

```hashread test.c```

```e /bin/ls```
