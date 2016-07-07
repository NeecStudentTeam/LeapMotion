/******************************************************************************\
* Copyright (C) 2012-2014 Leap Motion, Inc. All rights reserved.               *
* Leap Motion proprietary and confidential. Not for distribution.              *
* Use subject to the terms of the Leap Motion SDK Agreement available at       *
* https://developer.leapmotion.com/sdk_agreement, or another agreement         *
* between Leap Motion and you, your company or other organization.             *
\******************************************************************************/

#include <iostream>
#include <cstring>
#include "Leap.h"

using namespace Leap;

class SampleListener : public Listener {
  public:
    virtual void onInit(const Controller&);
    virtual void onConnect(const Controller&);
    virtual void onDisconnect(const Controller&);
    virtual void onExit(const Controller&);
    virtual void onFrame(const Controller&);
    virtual void onFocusGained(const Controller&);
    virtual void onFocusLost(const Controller&);
    virtual void onDeviceChange(const Controller&);
    virtual void onServiceConnect(const Controller&);
    virtual void onServiceDisconnect(const Controller&);

  private:
};

//�w�̖��O
const std::string fingerNames[] = {"�e�w", "�l�����w", "���w", "��w", "���w"};
//�w���̖��O
const std::string boneNames[] = {"���荜", "��ߍ�", "���ߍ�", "���ߍ�"};
//�W�F�X�`���[�̔F�����
const std::string stateNames[] = {"�F���Ȃ�", "�J�n", "�X�V", "�I��"};

//���X�i�[�̏����������@���X�i�[��ǉ��������ɌĂяo�����
void SampleListener::onInit(const Controller& controller) {
  std::cout << "�W�F�X�`���[���擾���܂��B" << std::endl;
}

//LeapMotion�Z���T�[�Ɛڑ����ꂽ�Ƃ��ɌĂяo�����
void SampleListener::onConnect(const Controller& controller) {
  std::cout << "LeapMotion�Ɛڑ�����܂����B" << std::endl;

  //�W�F�X�`���[�̓o�^
  //�T�[�N��
  controller.enableGesture(Gesture::TYPE_CIRCLE);
  //�X���C�v
  //controller.enableGesture(Gesture::TYPE_SWIPE);
  //�L�[�^�b�v
  //controller.enableGesture(Gesture::TYPE_KEY_TAP);
  //�X�N���[���^�b�v
  //controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
  
}

//LeapMotion�Z���T�[����ؒf���ꂽ�Ƃ��Ăяo�����
void SampleListener::onDisconnect(const Controller& controller) {
  std::cout << "LeapMotion�Ɛؒf����܂����B" << std::endl;
}

//���X�i�[�̏I�������@���X�i�[���폜�������ɌĂяo�����
void SampleListener::onExit(const Controller& controller) {
  std::cout << "�I��" << std::endl;
}

//�t���[���̃f�[�^���X�V���ꂽ���ɌĂяo�����
//���[�V�����Z���T�[�̃f�[�^�͂��ׂĂ����ŏ��������
void SampleListener::onFrame(const Controller& controller) {
  
  const Frame frame = controller.frame();
  
  /*std::cout << "�t���[��ID: " << frame.id()
            << ", �F�����Ă����̐�: " << frame.hands().count()
            << ", �F�����Ă���w�̐�: " << frame.fingers().extended().count()
            << ", �F�����Ă���c�[���̐�: " << frame.tools().count()
            << ", �F�����Ă���W�F�X�`���[�̐�: " << frame.gestures().count() << std::endl;*/

  //std::cout << "�t���[����;" << frame.currentFramesPerSecond() << std::endl;


  HandList hands = frame.hands();
  for (HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl) {
    
	// ��̎擾
    const Hand hand = *hl;
    std::string handType = hand.isLeft() ? "����" : "�E��";
   
	//�擾���Ă����̏��
	/*std::cout << std::string(2, ' ') << handType << ", ���ID: " << hand.id()
              << ", ��̍��W: " << hand.palmPosition() << std::endl;*/
    
	/*------�w�A��̊ۂ݂���\���鋅�̌v�Z����----------
    //const Vector normal = hand.palmNormal();
    //const Vector direction = hand.direction();

    // ��̌X��,�J��,�p�x����v�Z����
    
	/*std::cout << std::string(2, ' ') <<  "pitch: " << direction.pitch() * RAD_TO_DEG << " degrees, "
              << "roll: " << normal.roll() * RAD_TO_DEG << " degrees, "
              << "yaw: " << direction.yaw() * RAD_TO_DEG << " degrees" << std::endl;*/
	
	//---------------------------------------------------

    // �r�̎擾
    /*Arm arm = hand.arm();
	std::cout << std::string(2, ' ') <<  "��̕���: " << arm.direction()
              << " ���̍��W: " << arm.wristPosition()
              << "  �I�̍��W" << arm.elbowPosition() << std::endl;*/

    // �w�̎擾
    const FingerList fingers = hand.fingers();
    for (FingerList::const_iterator fl = fingers.begin(); fl != fingers.end(); ++fl) {
      const Finger finger = *fl;
      
	  /*std::cout << std::string(4, ' ') <<  fingerNames[finger.type()]
                << " , �w��ID: " << finger.id()
                << ", ����: " << finger.length()
                << "mm, ��: " << finger.width() << std::endl;*/

      // �w���̎擾
      for (int b = 0; b < 4; ++b) {
        Bone::Type boneType = static_cast<Bone::Type>(b);
        Bone bone = finger.bone(boneType);
        
		/*std::cout << std::string(6, ' ') <<  boneNames[boneType]
                  << " , start: " << bone.prevJoint()
                  << ", end: " << bone.nextJoint()
                  << ", ����: " << bone.direction() << std::endl;*/
      }
    }
  }

  // �c�[���̎擾
  /*const ToolList tools = frame.tools();
  for (ToolList::const_iterator tl = tools.begin(); tl != tools.end(); ++tl) {
    const Tool tool = *tl;
    std::cout << std::string(2, ' ') <<  "Tool, id: " << tool.id()
              << ", ���W: " << tool.tipPosition()
              << ", ����: " << tool.direction() << std::endl;
  }*/

  // �W�F�X�`���[�̎擾
  const GestureList gestures = frame.gestures();
  for (int g = 0; g < gestures.count(); ++g) {
    Gesture gesture = gestures[g];


    switch (gesture.type()) {
	  
	  //�T�[�N��
      case Gesture::TYPE_CIRCLE:
      {
        CircleGesture circle = gesture;
        std::string clockwiseness;


		//�T�[�N���̕���
        if (circle.pointable().direction().angleTo(circle.normal()) <= PI/2) {
          clockwiseness = "���v����";
        } else {
          clockwiseness = "�����v����";
        }

        // �p�x�̌v�Z
        float sweptAngle = 0;
        if (circle.state() != Gesture::STATE_START) {
          CircleGesture previousUpdate = CircleGesture(controller.frame(1).gesture(circle.id()));
          sweptAngle = (circle.progress() - previousUpdate.progress()) * 2 * PI;
        }
        
		
		std::cout << std::string(2, ' ')
                  << "�T�[�N��ID: " << gesture.id()
                  << ", �W�F�X�`���[�̏��: " << stateNames[gesture.state()]
                  << ", �T�[�N���̐i�s��: " << circle.progress()
                  << ", ���a: " << circle.radius()
                  << ", �p�x " << sweptAngle * RAD_TO_DEG
                  <<  ", " << clockwiseness << std::endl;

        break;
      }

	  //�X���C�v
      case Gesture::TYPE_SWIPE:
      {
        SwipeGesture swipe = gesture;
        std::cout << std::string(2, ' ')
          << "�W�F�X�`���[ID: " << gesture.id()
          << ", �W�F�X�`���[�̏��: " << stateNames[gesture.state()]
          << ", ����: " << swipe.direction()
          << ", ���x: " << swipe.speed() << std::endl;
        break;
      }

	  //�L�[�^�b�v
      /*case Gesture::TYPE_KEY_TAP:
      {
        KeyTapGesture tap = gesture;
        std::cout << std::string(2, ' ')
          << "�W�F�X�`���[ID: " << gesture.id()
          << ", �W�F�X�`���[�̏��: " << stateNames[gesture.state()]
          << ", ���o�ʒu: " << tap.position()
          << ", ����: " << tap.direction()<< std::endl;
        break;
      }*/
	  


	  //�X�N���[���^�b�v
      /*case Gesture::TYPE_SCREEN_TAP:
      {
        ScreenTapGesture screentap = gesture;
        std::cout << std::string(2, ' ')
          << "�W�F�X�`���[ID: " << gesture.id()
          << ", �W�F�X�`���[�̏��: " << stateNames[gesture.state()]
          << ", ���o�ʒu: " << screentap.position()
          << ", ����: " << screentap.direction()<< std::endl;
        break;
      }*/

	  //�F�����ĂȂ��W�F�X�`���[
	  default:
        std::cout << std::string(2, ' ')  << "�F������ĂȂ��W�F�X�`���[�ł��B" << std::endl;
        break;
    }
  }

  /*if (!frame.hands().isEmpty() || !gestures.isEmpty()) {
    std::cout << std::endl;
  }*/

}

//�A�v���P�[�V�������A�N�e�B�u�ɂȂ������ɌĂяo�����
void SampleListener::onFocusGained(const Controller& controller) {
  std::cout << "�A�v���P�[�V�������A�N�e�B�u�ɂȂ�܂����B" << std::endl;
}

//�A�v���P�[�V�������A�N�e�B�u�łȂ��Ȃ������ɌĂяo�����
void SampleListener::onFocusLost(const Controller& controller) {
  std::cout << "�A�v���P�[�V�������A�N�e�B�u�ł͂Ȃ��Ȃ�܂����B" << std::endl;
}

//LeapMotion�R���g���[���[�̐ڑ�/�ؒf���ꂽ���ɌĂяo�����
void SampleListener::onDeviceChange(const Controller& controller) {
  std::cout << "LeapMotion�Ɛؒf����܂���" << std::endl;
  const DeviceList devices = controller.devices();

  for (int i = 0; i < devices.count(); ++i) {
    std::cout << "LeapMotionID: " << devices[i].toString() << std::endl;
    std::cout << "  �f�[�^�z�M���: " << (devices[i].isStreaming() ? "true" : "false") << std::endl;
  }
}

//LeapMotion�̃f�[�^���擾���Ă���Windows�T�[�r�X�Ɛڑ����ꂽ���ɌĂяo�����
void SampleListener::onServiceConnect(const Controller& controller) {
  std::cout << "Service Connected:Windows�T�[�r�X�Ɛڑ�����܂����B" << std::endl;
}

//LeapMotion�̃f�[�^���擾���Ă���Windows�T�[�r�X�Ɛؒf���ꂽ���ɌĂяo�����
void SampleListener::onServiceDisconnect(const Controller& controller) {
  std::cout << "Service Disconnected:Windows�T�[�r�X�Ɛؒf����܂����B" << std::endl;
}


//leapmotion���C���v���O����
int main(int argc, char** argv) {
  // ���X�i�[�̍쐬
  SampleListener listener;
  Controller controller;

  // �C�x���g���󂯂Ƃ郊�X�i�[��o�^
  controller.addListener(listener);

  //�N�����Ɉ�����"--bg"���ݒ肳��Ă����ꍇ�o�N�O���E���h���[�h�œ��삳����
  //�قƂ�ǂ̏ꍇ�o�b�N�O���E���h���[�h�œ��삷�鎖�ɂȂ邽�߉�����ȊO�ł�if�����R�����g�A�E�g����
  if (argc > 1 && strcmp(argv[1], "--bg") == 0)
    controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);

  // Enter�L�[���������܂ŏ����𑱂���
  std::cout << "�I������ꍇ��Enter�������Ă��������B" << std::endl;
  std::cin.get();

  // �I�����Ƀ��X�i�[���폜����
  controller.removeListener(listener);

  return 0;
}
