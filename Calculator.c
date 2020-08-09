#INCLUDE <16F887.H>
#DEVICE ADC=10 
#USE DELAY(CLOCK=4000000)
#FUSES INTRC_IO,NOWDT,NOPUT,NOMCLR,NOPROTECT,NOCPD,NOBROWNOUT
#FUSES NOIESO,NOFCMEN,NOLVP,NODEBUG,NOWRT,BORV21

#USE FAST_IO(A)
#USE FAST_IO(B)
#USE FAST_IO(C)
#USE FAST_IO(D)

#INCLUDE <LCD1.C>

INT A,B,R;
FLOAT FR,FA,FB;

VOID MAIN ()
{
   SET_TRIS_C(0XFF);
   LCD_INIT();
   
   WHILE (TRUE)
   {
      A=INPUT_C()&0B00111000;
      A=A>>3;
      B=INPUT_C()&0B00000111;
      FA=A;
      FB=B;
      SWITCH (INPUT_C()&0XC0)
      {
         CASE 0X00:
         R=A+B;
         LCD_GOTOXY(1,1);
         PRINTF(LCD_PUTC, "A + B =     \n%u + %u = %u      ",A,B,R);
         BREAK;
         
         CASE 0X40:
         IF(A>B)
         {
            R=A-B;
            LCD_GOTOXY(1,1);
            PRINTF(LCD_PUTC, "A - B =         \n%u - %u = %u       "A,B,R);
         }
         ELSE IF(A<B)
         {
            R=A-B;
            LCD_GOTOXY(1,1);
            PRINTF(LCD_PUTC, "A - B =         \n%u - %u = %d       "A,B,R);
         }
         ELSE
         {
            LCD_GOTOXY(1,1);
            PRINTF(LCD_PUTC, "A - B =         \n%u - %u = 0       "A,B);
         }
         BREAK;
         
         CASE 0X80:
         R=A*B;
         LCD_GOTOXY(1,1);
         PRINTF(LCD_PUTC, "A * B =         \n%u * %u = %u  "A,B,R);
         BREAK;
         
         CASE 0XC0:
         FR=FA/FB;
         IF(B==0)
         {
            LCD_GOTOXY(1,1);
            PRINTF(LCD_PUTC, "A / B =         \n%u / %u = ERROR     "A,B);
         }
         ELSE
         {
            LCD_GOTOXY(1,1);
            PRINTF(LCD_PUTC, "A / B =         \n%u / %u = %1.3g     "A,B,FR);
         }
         BREAK;
      }
   }
}
