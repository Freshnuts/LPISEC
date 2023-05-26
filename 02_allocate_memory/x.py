from pwn import *
context.terminal = ['tmux','splitw' ,'-h']

p = process('./test')

gdb.attach(p, "break main")

p.interactive()
