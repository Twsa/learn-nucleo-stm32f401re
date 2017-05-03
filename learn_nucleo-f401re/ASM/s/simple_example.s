    ;simple_example
	PRESERVE8 ;表示这里的代码需要双字栈对齐
	THUMB ;表示使用的是THUMB代码
	AREA |.text|,CODE,READONLY  ;CODE区域起始
    EXPORT _main
    ENTRY	         ;main函数入口
_main FUNCTION
	;;初始化寄存器
	;MOV r0,#10  ;初始化循环计数器
	;MOV r1,#0   ;初始化结果
	;;计算10+9+8+...+1
;loop
    ;ADD r1,r0   ;R1=R1 + R0
	;SUBS r0,#1  ;减小R0，更新标志("S"后缀)
	;BNE loop    ;若结果非0，则跳到loop，结果位于R1中
;deadloop
    ;B deadloop  ;无限循环
	ENDFUNC
	END         ;文件结束
