
build/test:     file format elf64-x86-64


Disassembly of section .text:

0000000000600490 <main-0x31>:
  600490:	31 ed                	xor    ebp,ebp
  600492:	49 89 d1             	mov    r9,rdx
  600495:	5e                   	pop    rsi
  600496:	48 89 e2             	mov    rdx,rsp
  600499:	48 83 e4 f0          	and    rsp,0xfffffffffffffff0
  60049d:	50                   	push   rax
  60049e:	54                   	push   rsp
  60049f:	45 31 c0             	xor    r8d,r8d
  6004a2:	31 c9                	xor    ecx,ecx
  6004a4:	48 8b 3d 2d 02 20 00 	mov    rdi,QWORD PTR [rip+0x20022d]        # 8006d8 <printf@plt+0x2001b8>
  6004ab:	ff 15 2f 02 20 00    	call   QWORD PTR [rip+0x20022f]        # 8006e0 <printf@plt+0x2001c0>
  6004b1:	f4                   	hlt
  6004b2:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
  6004b9:	00 00 00 
  6004bc:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
  6004c0:	c3                   	ret

00000000006004c1 <main>:
  6004c1:	55                   	push   rbp
  6004c2:	48 89 e5             	mov    rbp,rsp
  6004c5:	48 81 ec 00 00 00 00 	sub    rsp,0x0
  6004cc:	48 8d 05 5d 00 20 00 	lea    rax,[rip+0x20005d]        # 800530 <printf@plt+0x200010>
  6004d3:	48 89 c7             	mov    rdi,rax
  6004d6:	b8 00 00 00 00       	mov    eax,0x0
  6004db:	e8 40 00 00 00       	call   600520 <printf@plt>
  6004e0:	b8 01 00 00 00       	mov    eax,0x1
  6004e5:	c9                   	leave
  6004e6:	c3                   	ret

Disassembly of section .init:

00000000006004e8 <.init>:
  6004e8:	48 83 ec 08          	sub    rsp,0x8
  6004ec:	48 8b 05 f5 01 20 00 	mov    rax,QWORD PTR [rip+0x2001f5]        # 8006e8 <printf@plt+0x2001c8>
  6004f3:	48 85 c0             	test   rax,rax
  6004f6:	74 02                	je     6004fa <main+0x39>
  6004f8:	ff d0                	call   rax
  6004fa:	48 83 c4 08          	add    rsp,0x8
  6004fe:	c3                   	ret

Disassembly of section .fini:

0000000000600500 <.fini>:
  600500:	48 83 ec 08          	sub    rsp,0x8
  600504:	48 83 c4 08          	add    rsp,0x8
  600508:	c3                   	ret

Disassembly of section .plt:

0000000000600510 <printf@plt-0x10>:
  600510:	ff 35 aa 01 20 00    	push   QWORD PTR [rip+0x2001aa]        # 8006c0 <printf@plt+0x2001a0>
  600516:	ff 25 ac 01 20 00    	jmp    QWORD PTR [rip+0x2001ac]        # 8006c8 <printf@plt+0x2001a8>
  60051c:	00 00                	add    BYTE PTR [rax],al
	...

0000000000600520 <printf@plt>:
  600520:	ff 25 aa 01 20 00    	jmp    QWORD PTR [rip+0x2001aa]        # 8006d0 <printf@plt+0x2001b0>
  600526:	68 00 00 00 00       	push   0x0
  60052b:	e9 e0 ff ff ff       	jmp    600510 <main+0x4f>
