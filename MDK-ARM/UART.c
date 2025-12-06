#include "uart.h"

uint8_t 	uart_tx_buffer 		[UART_TX_BUFFER_SIZE];
uint8_t 	uart_rx_buffer		[UART_RX_BUFFER_SIZE];
uint8_t 	uart_rx_cmd		[UART_CMD_SIZE];	
uint8_t 	uart_rx_data		[UART_DATA_SIZE];	

void uart_rx_handler(uint8_t *uart_rx_buffer)
{
	flag_uart_rx = 0;
		
	memcpy(uart_rx_cmd, &uart_rx_buffer[0], UART_CMD_SIZE); 
	memcpy(uart_rx_data, &uart_rx_buffer[UART_CMD_SIZE], UART_DATA_SIZE); 	
		
	if (strncmp((char *)uart_rx_cmd, UART_MOTOR_START, UART_CMD_SIZE) == 0)
	{
		motor.enable = true;
	}
	else if (strncmp((char *)uart_rx_cmd, UART_MOTOR_STOP, UART_CMD_SIZE) == 0)
	{
		motor.enable = false;
	}
	else if (strncmp((char *)uart_rx_cmd, UART_MOTOR_INVERSE, UART_CMD_SIZE) == 0)
	{
		motor.direction = !motor.direction;
	}
	else if (strncmp((char *)uart_rx_cmd, UART_MOTOR_SPEED, UART_CMD_SIZE) == 0)
	{
		uint8_t setpoint = atoi((char *)uart_rx_data);
		motor_PID_config.setpoint = setpoint;
	}
	else if (strncmp((char *)uart_rx_cmd, UART_MOTOR_PID, UART_CMD_SIZE) == 0)
	{
		motor_PID_config.Kp = uart_rx_data[9] - '0' + (uart_rx_data[10] - '0') / 10.0f;
		motor_PID_config.Ki  = uart_rx_data[11] - '0' + (uart_rx_data[12] - '0') / 10.0f;
		motor_PID_config.Kd = uart_rx_data[13] - '0' + (uart_rx_data[14] - '0') / 10.0f;
	}
	else if (strncmp((char *)uart_rx_cmd, UART_MOTOR_FREQUENCY, UART_CMD_SIZE) == 0)
	{
		motor.f_PWM = atoi((char *)uart_rx_data);
		frequency_control(&htim1, motor.f_PWM);
	}
	else if (strncmp((char *)uart_rx_cmd, UART_MOTOR_PLOT, UART_CMD_SIZE) == 0)
	{
		flag_uart_plot = !flag_uart_plot;		
	}
	
	memset(uart_rx_buffer, 0, UART_RX_BUFFER_SIZE);
}