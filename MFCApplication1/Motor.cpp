#include "LTDMC.h"
#include "Motor.h"

Motor::Motor()
{
	m_Speed = 10000;
}

void Motor::SetSpeed(int speed)
{
	m_Speed = speed;
}

int Motor::GetSpeed()
{
	return m_Speed;
}

void Motor::Init()
{
	dmc_board_init();
	dmc_set_pulse_outmode(0, 0, 2);
	dmc_set_counter_inmode(0, 0, 3);

	dmc_set_sevon_enable(0, 0, 1);
	dmc_stop(0, 0, 1);
	dmc_set_profile(0, 0, 0, m_Speed, 0.1, 1, 0);
	dmc_set_s_profile(0, 0, 0, 0);
	dmc_set_position_unit(0, 0, 0);
	dmc_set_position(0, 0, 0);

}

void Motor::Start()
{
	// 电机启动
	dmc_vmove(0, 0, 1);
	// 进料带启动
	dmc_write_outbit(0, 4, 0);
	// 振动盘启动
	dmc_write_outbit(0, 24, 0);
}

void Motor::Stop()
{
	dmc_write_outbit(0, 4, 1);		// 进料关闭 
	dmc_write_outbit(0, 24, 1);
	dmc_stop(0, 0, 0);				// 电机停止
}