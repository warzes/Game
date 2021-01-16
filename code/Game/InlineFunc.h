#pragma once

// ���������� �������������� warning C4191 (���� PROC)
// https://stackoverflow.com/questions/4192058/how-to-address-c4191-warning-around-calls-to-getprocaddress-with-farproc
template<typename Result, typename Original>
inline Result function_cast(Original fptr)
{
	return reinterpret_cast<Result>(reinterpret_cast<void*>(fptr));
}