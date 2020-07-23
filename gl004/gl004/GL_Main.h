//#pragma comment(linker,"/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#include<iostream>
#include<algorithm>
#include<gl/glut.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<stack>
//#include"Matrix.h"
using namespace std;
static  GLfloat step_angle=10;
extern const GLdouble Pi;



bool vvCrossProduct(double vec1[3], double vec2[3], double vec[3])//������˼��㣨vec1 x vec2��
{ 
	vec[0]=0.0; 
	vec[1]=0.0; 
	vec[2]=0.0;

	vec[0]=vec1[1]*vec2[2]-vec1[2]*vec2[1]; 
	vec[1]=vec1[2]*vec2[0]-vec1[0]*vec2[2]; 
	vec[2]=vec1[0]*vec2[1]-vec1[1]*vec2[0];
	if(fabs(vec[0])< 0.00001)vec[0]=0.0;
	if(fabs(vec[1])< 0.00001)vec[1]=0.0;
	if(fabs(vec[2])< 0.00001)vec[2]=0.0;

	return true;
}
bool Rotate(GLfloat angle,GLfloat pre[3],GLfloat post[3])
{

}
class Planet
{
public:
	GLfloat Color[4];//��ɫ
	GLfloat SelfPeriod;//�Դ�����
	GLfloat Redius;//�뾶
	GLfloat RevolutionPeriods;//��ת����
	GLfloat RevolutionRedius;//��ת�뾶
	Planet* Father;
	GLfloat CurrRevaltionAngle;
    GLfloat CurrSelfAngle;
    GLint slices;
	GLint stacks;
	//������ĳ�ʼ��
	Planet(GLfloat color[4],GLfloat selfPeriod,GLfloat redius,
		 GLfloat revolutionPeriods,GLfloat revolutionRedius,
		 Planet* father,GLfloat currRevaltionAngle, GLfloat currSelfAngle){
	    Color[0]=color[0];
		Color[1]=color[1];
		Color[2]=color[2];
		Color[3]=color[3];
		SelfPeriod=selfPeriod;
		Redius=redius;
		RevolutionPeriods=revolutionPeriods;
		RevolutionRedius=revolutionRedius;
		Father=father;
		CurrRevaltionAngle=currRevaltionAngle;
		CurrSelfAngle=currSelfAngle;
		slices=10;
		stacks=10;
	}
	//����Ĺ������ԣ���ת���ڣ���ת���ڣ��뾶����ת�뾶����ת������ɫ����ǰ��ת�Ƕȣ���ǰ�Դ��Ƕ�
void glutCircle(GLfloat redius,GLint slices)
{
	GLfloat step=2.0*Pi/slices;
	glBegin(GL_LINE_LOOP);
	for(int i=0;i<slices;i++)
		glVertex3f(redius*cos(i*step),0,redius*sin(i*step));
	glEnd();
}
	void SetModelslices_stack(GLint sl,GLint st){
	    slices=sl;
		stacks=st;
	}
	//�������Ϊ��
	void Model()//�����������Ϊ
	{
		
		{//���Ƶ���Ĳ��ʲ����Ƶ���
		    GLfloat sun_mat_ambient[4]={0,0,0,1.0};//���ֹ������䵽�ò����ϣ������ܶ�η�������������ڻ��� �еĹ���ǿ�ȣ�
	        GLfloat sun_mat_diffuse[4]={1,0,0,1.0};//�������䵽�ò����Ͼ����������γɵĹ���ǿ�ȣ���
	        GLfloat sun_mat_specular[4]={0,1,0,1.0};//�������䵽�ò����ϣ��������淴����γɵĹ���ǿ�ȣ���
//	        GLfloat sun_mat_emission[4]={0.5,0.5,0.5,1.0};//��ʾ���ʵ���ɫ��ԭ�������ʵ���һ�ֵĹ�Դ������Դǿ�Ⱥ���������Ի����������������Ӱ��
		    GLfloat sun_mat_shininess=60;//����ָ����	ȡֵ��Χ0-128��ԽС��ʾ���ʱ���Խ�ֲڣ��������ɢ�Ĺ�ߣ�Խ��Խ�⻬������������еĹ��
	        
		    
		    glMaterialfv(GL_FRONT,GL_AMBIENT,sun_mat_ambient);//���ò��ʵĸ�������
		    glMaterialfv(GL_FRONT,GL_DIFFUSE,sun_mat_diffuse);
		    glMaterialfv(GL_FRONT,GL_SPECULAR,sun_mat_specular);
		    glMaterialfv(GL_FRONT,GL_EMISSION,Color);
	 	    glMaterialf(GL_FRONT,GL_SHININESS,sun_mat_shininess);		
	    }
		glMatrixMode(GL_MODELVIEW);//����ͶӰ����
	    glLoadIdentity();//��λ��

		Planet* currSatr=this;
		stack<Planet*> tempstack;
		while(currSatr->Father!=NULL)
		{
			tempstack.push(currSatr);
			currSatr=currSatr->Father;
		}
		while(!tempstack.empty())
		{
			Planet* temp=tempstack.top();
			glRotatef(temp->CurrRevaltionAngle,0,1.0,0.0);
			glTranslatef(temp->RevolutionRedius,0,0.0);

			tempstack.pop();
		}
		glutSolidSphere(Redius, slices, stacks); 
//		glEmptyMatrix();

		CurrRevaltionAngle+=360/RevolutionPeriods;//��ǰ��ת�Ƕ�ǰ��һ��
		if(CurrRevaltionAngle>360.0)
			CurrRevaltionAngle=0.0;
	}
	void drawpath()//�������ǹ�ת�Ĺ켣
	{
		Planet* currSatr=this;
		stack<Planet*> tempstack;
		while(currSatr->Father!=NULL)
		{
			tempstack.push(currSatr->Father);
			currSatr=currSatr->Father;
		}
		while(!tempstack.empty())
		{
			Planet* temp=tempstack.top();
			glRotatef(temp->CurrRevaltionAngle,0,1.0,0.0);
			glTranslatef(temp->RevolutionRedius,0,0.0);
			tempstack.pop();
		}
		glutCircle(this->RevolutionRedius,slices*2);
	}
};
class SolarSystem
{
   GLfloat curralfa_right_left;//��ǰ����ԭʼ����ĽǶ�
   GLfloat curralfa_up_down;
   GLfloat scale;
   GLfloat cameraposion[3];//�����λ�ò���
   Planet*  planets[20] ;//�����Դ��10������
   GLint NUM;
   public:
   SolarSystem()
   {
	   for(int i=0;i<20;i++)
		   planets[i]=NULL;
	   NUM=0;
	   cameraposion[0]=100;
	   cameraposion[1]=300;
	   cameraposion[2]=100;
	   scale=1.0;
   }
   void AddPlanet(Planet* self)
   {
	   planets[NUM]=self;
	   NUM++;
   }
   void camera()
   {
	   glMatrixMode(GL_PROJECTION);//����ͶӰ����
	   glLoadIdentity();//��λ��//����������
	   //���������λ��
	   glRotatef(curralfa_right_left,0.0,1.0,0.0);
	   gluPerspective(90,1.0,1.0,1000000);//����׶ʵ��ĳߴ��С
	   
       gluLookAt(cameraposion[0],cameraposion[1],cameraposion[2],   0,0,0,   0.0,1,0.0);//��������ķ�λ
   }
   //���ù�������
   void SetLight(GLint numoflight,GLfloat position[4],GLfloat ambient[4],GLfloat diffuse[4],GLfloat specular[4])
   {
	//                       ��ʾ�����ڻ����о������淴������õ��Ĺ���ǿ�ȣ��˴�Ϊ�׹�
	    glLightfv(numoflight,GL_POSITION,position);//����light0�Ź�Դ������
	    glLightfv(numoflight,GL_AMBIENT,ambient);
	    glLightfv(numoflight,GL_DIFFUSE,diffuse);
	    glLightfv(numoflight,GL_SPECULAR,specular);
   }
   void display(void)
   {
	   glClearColor(0.0,0.0, 0.0,1.0); //���������ɫ����ɫ
	   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//�������	
//	   glColor3f(0.0,1.0, 0.0); //���õ�ǰʹ����ɫ����ɫ
	   GLint w = glutGet(GLUT_WINDOW_WIDTH);//��ȡ��ǰ���ڳߴ��С����λ������
       GLint h = glutGet(GLUT_WINDOW_HEIGHT);
	   if(w>h)
	       glViewport(0,0, h, h); //����ȫ���ӿ�
	   else
		   glViewport(0,0, w, w); //����ȫ���ӿ�
	
	   camera();//���������λ����ߴ��뷽λ
	   glMatrixMode(GL_MODELVIEW);//����ͶӰ����
	   glLoadIdentity();//��λ��//����������
	   glColor3f(0.0,1.0,0.0);
	   glBegin(GL_LINES);
	   glVertex3f(10000000,0,0);
	   glVertex3f(-10000000,0,0);
	   glVertex3f(0,0,10000000);
	   glVertex3f(0,0,-10000000);
	   glEnd();


	   glMatrixMode(GL_MODELVIEW);//����ͶӰ����
	   glLoadIdentity();//��λ��
	   GLfloat sun_light_position[4]={0,0,0,1.0};//�����Դ��λ�ã���[3]==0,���Դλ������Զ�������Թ��ƽ�й⣩:�˴�Ϊλ�ù⣬λ��(0,0,0)
	   GLfloat sun_light_ambient[4]={0,0,0,1.0};//ΪglLight*�� ����������ʾ�����ڻ����о����˷����������ڻ����е�ǿ�ȣ���ɫ����RRGA��ʾ:�˴����Ϊ�ڹ�
	   GLfloat sun_light_diffuse[4]={1,1,1,1.0};//ΪΪglLight*�� ����������ʾ�����ڻ����о�������������õ��Ĺ���ǿ�ȣ�:�˴�Ϊ�׹�
	   GLfloat sun_light_specular[4]={1,1,1,1.0};//  
	   SetLight(GL_LIGHT0,sun_light_position,sun_light_ambient,sun_light_diffuse,sun_light_specular);//����0�Ź�Դ�����ԣ�λ�ù�
	   sun_light_position[0]=1.0;
	   sun_light_position[3]=0.0;
	   SetLight(GL_LIGHT1,sun_light_position,sun_light_ambient,sun_light_diffuse,sun_light_specular);//����1�Ź�Դ�����ԣ������
	   glEnable(GL_LIGHT0);//����light0��
	   glEnable(GL_LIGHT1);//����light1��
	   glEnable(GL_LIGHTING);//��ʼ�������չ���
	   glEnable(GL_DEPTH_TEST);
	   glLoadIdentity();//��λ��
	   for(int i=0;i<NUM;i++)
		   planets[i]->drawpath();//���λ�������
	   glLoadIdentity();//��λ��
	   for(int i=0;i<NUM;i++)
		   planets[i]->Model();//���λ�������ģ��

	   glutSwapBuffers();//��ʾͼ��

   }

   void redisplay()
   {
	   GLint w = glutGet(GLUT_WINDOW_WIDTH);//��ȡ��ǰ���ڳߴ��С����λ������
       GLint h = glutGet(GLUT_WINDOW_HEIGHT);
	   if(w>h)
	       glViewport(0,0, h, h); //����ȫ���ӿ�
	   else
		   glViewport(0,0, w, w); //����ȫ���ӿ�

   }

   void  ResponseFunction(unsigned char key, int x, int y)
   {
	   switch(key)
	   {
	   case '+':
	   {
	    cameraposion[0]*=1.1;
	    cameraposion[1]*=1.1;
	    cameraposion[2]*=1.1;
	   }
	   break;
	   case '-':
		   {
			   cameraposion[0]*=0.9;
			   cameraposion[1]*=0.9;
			   cameraposion[2]*=0.9;
		   }
		   break;
	   
	   default:
		   break;
	   }
	   
	   camera();
   }
   void ResponseFunction_special(int key, int x, int y)
   {
	   switch(key)
	   {
	   case GLUT_KEY_LEFT:
		   {
			   curralfa_right_left+=5;
			   if(curralfa_right_left>360)
				   curralfa_right_left=0;			   
		   }
		   break;
	   case GLUT_KEY_RIGHT:
		   {
			   curralfa_right_left-=5;
			   if(curralfa_right_left<-360)
				   curralfa_right_left=0;
		   }	   
		   break;
	   case GLUT_KEY_UP:
		   break;
	   case GLUT_KEY_DOWN:
		   break;
	   default:
		   break;
	   }
	   camera();
   }
};
