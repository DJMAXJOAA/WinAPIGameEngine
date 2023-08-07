#pragma once
class CObject;

void CreateObj(CObject* _pObj, GROUP_TYPE _eGroup);
void DeleteObj(CObject* _pObj);
void ChangeScene(SCENE_TYPE _eNext);


// Clear Vector Container
template<typename T>
void SafeDeleteVec(vector<T>& _vec)
{
	for (size_t i = 0; i < _vec.size(); i++)
	{
		if (_vec[i] != nullptr)
			delete _vec[i];
	}
	_vec.clear();
}