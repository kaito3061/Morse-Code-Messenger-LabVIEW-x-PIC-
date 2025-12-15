#include <819-.h>
#use delay(clock=8000000) // 8MHz動作
#include <setups.c>
#include <init.c>
#include <stdlib.h>

// --- 定数定義 ---
#define UNIT_MS 200           // トン(・)の長さ [ms]
#define DASH_MS (UNIT_MS * 3) // ツー(－)の長さ [ms]

#define LED_PIN PIN_B2        // LEDのピン
#define SPK_PIN PIN_B3        // スピーカーのピン (今回追加)

// --- 通信設定 ---
#use rs232(baud=9600,parity=N,xmit=PIN_A4,rcv=PIN_A2,bits=8)

// --- 音と光を出す関数 (Beep) ---
// msミリ秒の間、LEDを光らせながら、約1000Hzの音を出す
void beep(long ms) {
   long i;
   
   output_high(LED_PIN); // LED ON
   
   // 音を作るループ (1回1ms = 1000Hz)
   for(i = 0; i < ms; i++) {
      output_high(SPK_PIN);
      delay_us(500);       // 0.5ms High
      output_low(SPK_PIN);
      delay_us(500);       // 0.5ms Low
   }
   
   output_low(LED_PIN);  // LED OFF
   output_low(SPK_PIN);  // 音もOFF
}

// --- モールス信号生成用関数 ---

// トン(・)
void dot() {
   beep(UNIT_MS);         // 音と光 ON
   delay_ms(UNIT_MS);     // 符号間の休み (無音・消灯)
}

// ツー(－)
void dash() {
   beep(DASH_MS);         // 音と光 ON (長)
   delay_ms(UNIT_MS);     // 符号間の休み
}

// 文字を解析して再生する関数
void play_morse(char c) {
   // 小文字なら大文字に変換
   if(c >= 'a' && c <= 'z') {
      c = c - 0x20;
   }

   switch(c) {
      case 'A': dot(); dash(); break;
      case 'B': dash(); dot(); dot(); dot(); break;
      case 'C': dash(); dot(); dash(); dot(); break;
      case 'D': dash(); dot(); dot(); break;
      case 'E': dot(); break;
      case 'F': dot(); dot(); dash(); dot(); break;
      case 'G': dash(); dash(); dot(); break;
      case 'H': dot(); dot(); dot(); dot(); break;
      case 'I': dot(); dot(); break;
      case 'J': dot(); dash(); dash(); dash(); break;
      case 'K': dash(); dot(); dash(); break;
      case 'L': dot(); dash(); dot(); dot(); break;
      case 'M': dash(); dash(); break;
      case 'N': dash(); dot(); break;
      case 'O': dash(); dash(); dash(); break;
      case 'P': dot(); dash(); dash(); dot(); break;
      case 'Q': dash(); dash(); dot(); dash(); break;
      case 'R': dot(); dash(); dot(); break;
      case 'S': dot(); dot(); dot(); break;
      case 'T': dash(); break;
      case 'U': dot(); dot(); dash(); break;
      case 'V': dot(); dot(); dot(); dash(); break;
      case 'W': dot(); dash(); dash(); break;
      case 'X': dash(); dot(); dot(); dash(); break;
      case 'Y': dash(); dot(); dash(); dash(); break;
      case 'Z': dash(); dash(); dot(); dot(); break;
      
      case '1': dot(); dash(); dash(); dash(); dash(); break;
      case '2': dot(); dot(); dash(); dash(); dash(); break;
      case '3': dot(); dot(); dot(); dash(); dash(); break;
      case '4': dot(); dot(); dot(); dot(); dash(); break;
      case '5': dot(); dot(); dot(); dot(); dot(); break;
      case '6': dash(); dot(); dot(); dot(); dot(); break;
      case '7': dash(); dash(); dot(); dot(); dot(); break;
      case '8': dash(); dash(); dash(); dot(); dot(); break;
      case '9': dash(); dash(); dash(); dash(); dot(); break;
      case '0': dash(); dash(); dash(); dash(); dash(); break;

      case ' ': delay_ms(UNIT_MS * 4); break;
      default: break;
   }
   
   // 文字間の休み
   delay_ms(UNIT_MS * 2);
}

void main()
{
   INT_IO();   // RB3もここで出力になります
   setups();
   
   // --- 起動確認 (LEDと音) ---
   int i;
   for(i=0; i<3; i++){
      beep(100);       // ピッ！(光る)
      delay_ms(100);   // シーン(消える)
   }

   // --- メインループ ---
   while(TRUE)
   {
      if(kbhit()) 
      {
         char data = getc();
         play_morse(data);
      }
   }
}