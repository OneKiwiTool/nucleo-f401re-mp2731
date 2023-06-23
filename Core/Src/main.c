#include "main.h"
#include "board.h"
#include "mp2731.h"
#include <stdio.h>

int main(void)
{
	//bit Fault;
    board_init();
    printf("\nStart Program MP2731!\n");

    mp2731_detect();
    mp2731_readRegisters();

    while (1)
    {
        led_toggle();
        HAL_Delay(1000);
    }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
