#include "LTDMC.h"
#include "Encoder.h"

Encoder::Encoder()
{
	m_EncoderData = 0;
}

Encoder::~Encoder()
{

}

void Encoder::Start()
{
	dmc_set_encoder(0, 0, 0);
}

void Encoder::Stop()
{
	dmc_set_dec_stop_time(0, 0, 1);	// ±àÂëÆ÷¹Ø±Õ
}

long Encoder::GetEncoderData()
{
	m_EncoderData = dmc_get_encoder(0, 0);
	return m_EncoderData;
}