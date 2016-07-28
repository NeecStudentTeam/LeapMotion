#include <iostream>
#include <cstring>
#include <string>
#include "Leap.h"

using namespace Leap;

class MotionListener : public Listener {
public:
	virtual void onInit(const Controller&);
	virtual void onConnect(const Controller&);
	virtual void onDisconnect(const Controller&);
	virtual void onExit(const Controller&);
	virtual void onFrame(const Controller&);
	virtual void onFocusGained(const Controller&);
	virtual void onFocusLost(const Controller&);
	virtual void onDeviceChange(const Controller&);
	
	//�W�F�X�`���[ID
	int gestureID;

private:
};
//���X�i�[�̏����������@���X�i�[��ǉ��������ɌĂяo�����
void MotionListener::onInit(const Controller& controller) {
	std::cout << "�J�n" << std::endl;
}

//LeapMotion�Z���T�[�Ɛڑ����ꂽ�Ƃ��ɌĂяo�����
void MotionListener::onConnect(const Controller& controller) {
	std::cout << "LeapMotion�Ɛڑ�����܂����B" << std::endl;

	//�W�F�X�`���[�̗L����
	//�T�[�N��
	controller.enableGesture(Gesture::TYPE_CIRCLE);
	//�X���C�v
	controller.enableGesture(Gesture::TYPE_SWIPE);

	//�댟�m�������炷�ׂɐݒ��ύX�@�����S�ɖ����Ȃ�킯�ł͂Ȃ�	
	controller.config().setFloat("Gesture.Circle.MinArc", 2 * PI);
	controller.config().save();
}

//LeapMotion�Z���T�[����ؒf���ꂽ�Ƃ��Ăяo�����
void MotionListener::onDisconnect(const Controller& controller) {
	std::cout << "LeapMotion�Ɛؒf����܂����B" << std::endl;
}

//���X�i�[�̏I�������@���X�i�[���폜�������ɌĂяo�����
void MotionListener::onExit(const Controller& controller) {
	std::cout << "�I��" << std::endl;
}

//�t���[���̃f�[�^���X�V���ꂽ���ɌĂяo�����
//���[�V�����Z���T�[�̃f�[�^�͂��ׂĂ����ŏ��������
void MotionListener::onFrame(const Controller& controller) {

	//�T�[�N�����v����
	bool clockwise = false;
	//�T�[�N�������v����
	bool counterClockwise = false;
	//�X���C�v�E����
	bool rightSwipe = false;
	//�X���C�v������
	bool leftSwipe = false;
	//�X���C�v�����
	bool upSwipe = false;
	//�X���C�v������
	bool downSwipe = false;	

	const Frame frame = controller.frame();
	
	// �W�F�X�`���[�̎擾
	const GestureList gestures = frame.gestures();
	for (int g = 0; g < gestures.count(); ++g) {
		Gesture gesture = gestures[g];

		switch (gesture.type()) {

		//�T�[�N��
		case Gesture::TYPE_CIRCLE:{
			CircleGesture circle = gesture;
			
			//�W�F�X�`���[�F���J�n
			if ((gesture.state() == Leap::Gesture::State::STATE_START)){
				std::cout << "�F���J�n" << std::endl;
				gestureID = gesture.id();
			}
			//�W�F�X�`���[�X�V��
			/*if ((gesture.state() == Leap::Gesture::State::STATE_UPDATE)){
				std::cout << "�X�V��" << std::endl;
			}*/
			//�W�F�X�`���[�F������
			if ((gesture.state() == Leap::Gesture::State::STATE_STOP)){
				//�T�[�N���̕���
				if (circle.pointable().direction().angleTo(circle.normal()) <= PI / 2) {
					clockwise = true;
				}
				else {
					counterClockwise = true;					
				}			
				//���v����
				if (clockwise){		
					std::cout << "ID" << gesture.id() << std::endl;
					//�w1�{
					if (frame.fingers().extended().count() == 1 && gestureID == gesture.id()){
						std::cout << "�e���r��_���܂�!!!!!!!!" << std::endl;
					}
					//�w3�{
					else if (frame.fingers().extended().count() == 3 && gestureID == gesture.id()){
						std::cout << "�G�A�R�������܂�!!!!!!!!" << std::endl;
					}
					//�w5�{
					else if (frame.fingers().extended().count() == 5 && gestureID == gesture.id()){
						std::cout << "�Ɩ���_���܂�!!!!!!!!" << std::endl;
					}
					else
					{
						std::cout << "clockwise���ݒ�" << std::endl;
						std::cout << "," << frame.fingers().extended().count() << std::endl;
					}
				}
				//�����v����
				if (counterClockwise){
					std::cout << "ID" << gesture.id() << std::endl;
					//�w1�{
					if (frame.fingers().extended().count() == 1 && gestureID == gesture.id()){
						std::cout << "�e���r�������܂�!!!!!!!!" << std::endl;
					}
					//�w3�{
					else if (frame.fingers().extended().count() == 3 && gestureID == gesture.id()){
						std::cout << "�G�A�R���������܂�!!!!!!!!" << std::endl;
					}
					//�w5�{
					else if (frame.fingers().extended().count() == 5 && gestureID == gesture.id()){
						std::cout << "�Ɩ��������܂�!!!!!!!!" << std::endl;
					}
					else
					{
						std::cout << "counter���ݒ�" << std::endl;
						std::cout << "," << frame.fingers().extended().count() << std::endl;
					}
				}
			}

			break;
		}
		//�X���C�v
		case Gesture::TYPE_SWIPE:{
			SwipeGesture swipe = gesture;

			//�W�F�X�`���[�F���J�n
			if ((gesture.state() == Leap::Gesture::State::STATE_START)){
				std::cout << "�F���J�n" << std::endl;
				gestureID = gesture.id();
			}
			//�W�F�X�`���[�X�V��
			/*if ((gesture.state() == Leap::Gesture::State::STATE_UPDATE)){
				std::cout << "�X�V��" << std::endl;
			}*/
			//�W�F�X�`���[�F������
			if ((gesture.state() == Leap::Gesture::State::STATE_STOP)){
				//�X���C�v�̕���
				if (swipe.direction().x > 0.7) {
					rightSwipe = true;
				}
				else if (swipe.direction().x < -0.7){
					leftSwipe = true;
				}
				else if (swipe.direction().y > 0.7) {
					upSwipe = true;
				}
				else if (swipe.direction().y < -0.7) {
					downSwipe = true;
				}
			}

			//�E�����X���C�v
			if (rightSwipe){
				//�w1�{
				if (frame.fingers().extended().count() == 1 && gestureID == gesture.id()){
					std::cout << "ID" << gesture.id() << std::endl;
					std::cout << "�`�����l����1�グ��!!!!!!!!" << std::endl;
				}
				else
				{
					std::cout << "right���ݒ�" << std::endl;
					std::cout << "," << frame.fingers().extended().count() << std::endl;
				}
			}
			//�������X���C�v
			if (leftSwipe){
				//�w1�{
				if (frame.fingers().extended().count() == 1 && gestureID == gesture.id()){
					std::cout << "ID" << gesture.id() << std::endl;
					std::cout << "�`�����l����1������!!!!!!!!" << std::endl;
				}
				else
				{
					std::cout << "left���ݒ�" << std::endl;
					std::cout << "," << frame.fingers().extended().count() << std::endl;
				}
			}
			//������X���C�v
			if (upSwipe){
				std::cout << "ID" << gesture.id() << std::endl;	
				//�w1�{
				if (frame.fingers().extended().count() == 1 && gestureID == gesture.id()){
					std::cout << "���ʂ�1�グ��!!!!!!!!" << std::endl;
				}
				//�w3�{
				else if (frame.fingers().extended().count() == 3 && gestureID == gesture.id()){
					std::cout << "���x��1�グ��!!!!!!!!" << std::endl;
				}
				else
				{
					std::cout << "up���ݒ�" << std::endl;
					std::cout << "," << frame.fingers().extended().count() << std::endl;
				}
			}
			//�������X���C�v
			if (downSwipe){
				std::cout << "ID" << gesture.id() << std::endl;
				//�w1�{
				if (frame.fingers().extended().count() == 1 && gestureID == gesture.id()){
					std::cout << "���ʂ�1������!!!!!!!!" << std::endl;
				}
				//�w3�{
				else if (frame.fingers().extended().count() == 3 && gestureID == gesture.id()){
					std::cout << "���x��1������!!!!!!!!" << std::endl;
				}
				else
				{
					std::cout << "���ݒ�" << std::endl;
					std::cout << "," << frame.fingers().extended().count() << std::endl;
				}
			}
			break;
		}

		//�F�����ĂȂ��W�F�X�`���[
		default:
			std::cout << std::string(2, ' ') << "�F������ĂȂ��W�F�X�`���[�ł��B" << std::endl;
			break;
		}
	}

	//���F�����Ă���Ƃ�
	/*if (!frame.hands().isEmpty() || !gestures.isEmpty()) {
	std::cout << "�F����" << std::endl;
	}*/

}

//�A�v���P�[�V�������A�N�e�B�u�ɂȂ������ɌĂяo�����
void MotionListener::onFocusGained(const Controller& controller) {
	std::cout << "�A�v���P�[�V�������A�N�e�B�u�ɂȂ�܂����B" << std::endl;
}

//�A�v���P�[�V�������A�N�e�B�u�łȂ��Ȃ������ɌĂяo�����
void MotionListener::onFocusLost(const Controller& controller) {
	std::cout << "�A�v���P�[�V�������A�N�e�B�u�ł͂Ȃ��Ȃ�܂����B" << std::endl;
}

//LeapMotion�R���g���[���[�̐ڑ�/�ؒf���ꂽ���ɌĂяo�����
void MotionListener::onDeviceChange(const Controller& controller) {
	std::cout << "LeapMotionController" << std::endl;
	const DeviceList devices = controller.devices();

	for (int i = 0; i < devices.count(); ++i) {
		std::cout << "LeapMotionID: " << devices[i].toString() << std::endl;
		std::cout << "  �f�[�^�z�M���: " << (devices[i].isStreaming() ? "true" : "false") << std::endl;
	}
}

//leapmotion���C���v���O����
int main(int argc, char** argv) {

	// ���X�i�[�̍쐬
	MotionListener listener;
	Controller controller;;	

	// �C�x���g���󂯂Ƃ郊�X�i�[��o�^
	controller.addListener(listener);

	//�o�b�N�O���E���h���[�h�œ��삳����
	controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);

	// Enter�L�[���������܂ŏ����𑱂���
	std::cout << "�I������ꍇ��Enter�������Ă�������" << std::endl;
	std::cin.get();

	// �I�����Ƀ��X�i�[���폜����
	controller.removeListener(listener);

	return 0;
}
