#include "BaseApplication.hpp"

int My::BaseApplication::Init(){
	m_bQuit = false;
	return 0;
}


void My::BaseApplication::Destroy(){


}


void My::BaseApplication::Update(){


}

bool My::BaseApplication::IsQuit(){

	return m_bQuit;
}
