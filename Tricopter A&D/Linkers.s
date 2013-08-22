.text

;.global _asmFunction
;_asmFunction:
;mov #0,w0
;mov w0,_cVariable
;return

;.global _main
;_main:
;call _foo
;return

.bss
.global _motor1
.global _motor2
.global _motor3
.global _motor4
.global _motor5
.global _motor6
.global PWMmotor1
.global PWMmotor2
.global PWMmotor3
.global PWMmotor4
.global PWMmotor5
.global PWMmotor6
.global PWMzerocheck
.global PWMperiod
.global PWMmotor1check
.global PWMmotor2check
.global PWMmotor3check
.global PWMmotor4check
.global PWMmotor5check
.global PWMmotor6check
.global Initperiodrestart
.align 2
_motor1: .space 2
_motor2: .space 2
_motor3: .space 2
_motor4: .space 2
_motor5: .space 2
_motor6: .space 2
PWMmotor1: .space 2
PWMmotor2: .space 2
PWMmotor3: .space 2
PWMmotor4: .space 2
PWMmotor5: .space 2
PWMmotor6: .space 2
PWMzerocheck: .space 2
PWMperiod: .space 2
PWMmotor1check: .space 2
PWMmotor2check: .space 2
PWMmotor3check: .space 2
PWMmotor4check: .space 2
PWMmotor5check: .space 2
PWMmotor6check: .space 2
Initperiodrestart: .space 2

.end
