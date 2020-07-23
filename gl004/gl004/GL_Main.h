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



bool vvCrossProduct(double vec1[3], double vec2[3], double vec[3])//向量叉乘计算（vec1 x vec2）
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
	GLfloat Color[4];//颜色
	GLfloat SelfPeriod;//自传周期
	GLfloat Redius;//半径
	GLfloat RevolutionPeriods;//公转周期
	GLfloat RevolutionRedius;//公转半径
	Planet* Father;
	GLfloat CurrRevaltionAngle;
    GLfloat CurrSelfAngle;
    GLint slices;
	GLint stacks;
	//对星球的初始化
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
	//星球的共有特性，自转周期，公转周期，半径，公转半径，公转对象，颜色，当前公转角度，当前自传角度
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
	//星球的行为：
	void Model()//绘制星球的行为
	{
		
		{//定制地球的材质并绘制地球
		    GLfloat sun_mat_ambient[4]={0,0,0,1.0};//各种光线照射到该材质上，经过很多次反射后，最终遗留在环境 中的光线强度，
	        GLfloat sun_mat_diffuse[4]={1,0,0,1.0};//光线照射到该材质上经过漫反射形成的光线强度：红
	        GLfloat sun_mat_specular[4]={0,1,0,1.0};//光线照射到该材质上，经过镜面反射后形成的光线强度：蓝
//	        GLfloat sun_mat_emission[4]={0.5,0.5,0.5,1.0};//表示材质的颜色：原理：将材质当成一种的光源，当光源强度很弱，不会对环境中其他物体产生影响
		    GLfloat sun_mat_shininess=60;//镜面指数，	取值范围0-128，越小表示材质表面越粗糙，会产生分散的光斑；越大越光滑，会产生交集中的光斑
	        
		    
		    glMaterialfv(GL_FRONT,GL_AMBIENT,sun_mat_ambient);//设置材质的各种属性
		    glMaterialfv(GL_FRONT,GL_DIFFUSE,sun_mat_diffuse);
		    glMaterialfv(GL_FRONT,GL_SPECULAR,sun_mat_specular);
		    glMaterialfv(GL_FRONT,GL_EMISSION,Color);
	 	    glMaterialf(GL_FRONT,GL_SHININESS,sun_mat_shininess);		
	    }
		glMatrixMode(GL_MODELVIEW);//设置投影矩阵
	    glLoadIdentity();//单位化

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

		CurrRevaltionAngle+=360/RevolutionPeriods;//当前公转角度前进一天
		if(CurrRevaltionAngle>360.0)
			CurrRevaltionAngle=0.0;
	}
	void drawpath()//绘制行星公转的轨迹
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
   GLfloat curralfa_right_left;//当前的与原始相机的角度
   GLfloat curralfa_up_down;
   GLfloat scale;
   GLfloat cameraposion[3];//相机的位置参数
   Planet*  planets[20] ;//最多可以存放10个物体
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
	   glMatrixMode(GL_PROJECTION);//设置投影矩阵
	   glLoadIdentity();//单位化//绘制坐标轴
	   //设置相机的位置
	   glRotatef(curralfa_right_left,0.0,1.0,0.0);
	   gluPerspective(90,1.0,1.0,1000000);//设置锥实体的尺寸大小
	   
       gluLookAt(cameraposion[0],cameraposion[1],cameraposion[2],   0,0,0,   0.0,1,0.0);//设置相机的方位
   }
   //设置光照类型
   void SetLight(GLint numoflight,GLfloat position[4],GLfloat ambient[4],GLfloat diffuse[4],GLfloat specular[4])
   {
	//                       表示光线在环境中经过镜面反射后所得到的光线强度：此处为白光
	    glLightfv(numoflight,GL_POSITION,position);//配置light0号光源的属性
	    glLightfv(numoflight,GL_AMBIENT,ambient);
	    glLightfv(numoflight,GL_DIFFUSE,diffuse);
	    glLightfv(numoflight,GL_SPECULAR,specular);
   }
   void display(void)
   {
	   glClearColor(0.0,0.0, 0.0,1.0); //设置清除颜色：黑色
	   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//清除函数	
//	   glColor3f(0.0,1.0, 0.0); //设置当前使用颜色：绿色
	   GLint w = glutGet(GLUT_WINDOW_WIDTH);//获取当前窗口尺寸大小：单位：像素
       GLint h = glutGet(GLUT_WINDOW_HEIGHT);
	   if(w>h)
	       glViewport(0,0, h, h); //设置全局视口
	   else
		   glViewport(0,0, w, w); //设置全局视口
	
	   camera();//设置相机的位置与尺寸与方位
	   glMatrixMode(GL_MODELVIEW);//设置投影矩阵
	   glLoadIdentity();//单位化//绘制坐标轴
	   glColor3f(0.0,1.0,0.0);
	   glBegin(GL_LINES);
	   glVertex3f(10000000,0,0);
	   glVertex3f(-10000000,0,0);
	   glVertex3f(0,0,10000000);
	   glVertex3f(0,0,-10000000);
	   glEnd();


	   glMatrixMode(GL_MODELVIEW);//设置投影矩阵
	   glLoadIdentity();//单位化
	   GLfloat sun_light_position[4]={0,0,0,1.0};//定义光源的位置，若[3]==0,则光源位置无限远（方向性光或平行光）:此处为位置光，位置(0,0,0)
	   GLfloat sun_light_ambient[4]={0,0,0,1.0};//为glLight*第 个参数，表示光线在环境中经过此反射后最后留在环境中的强度（颜色）用RRGA表示:此处最后为黑光
	   GLfloat sun_light_diffuse[4]={1,1,1,1.0};//为为glLight*第 个参数，表示光线在环境中经过漫反射后所得到的光线强度，:此处为白光
	   GLfloat sun_light_specular[4]={1,1,1,1.0};//  
	   SetLight(GL_LIGHT0,sun_light_position,sun_light_ambient,sun_light_diffuse,sun_light_specular);//设置0号光源的属性：位置光
	   sun_light_position[0]=1.0;
	   sun_light_position[3]=0.0;
	   SetLight(GL_LIGHT1,sun_light_position,sun_light_ambient,sun_light_diffuse,sun_light_specular);//设置1号光源的属性：方向光
	   glEnable(GL_LIGHT0);//开启light0号
	   glEnable(GL_LIGHT1);//开启light1号
	   glEnable(GL_LIGHTING);//开始环境光照功能
	   glEnable(GL_DEPTH_TEST);
	   glLoadIdentity();//单位化
	   for(int i=0;i<NUM;i++)
		   planets[i]->drawpath();//依次绘制球体
	   glLoadIdentity();//单位化
	   for(int i=0;i<NUM;i++)
		   planets[i]->Model();//依次绘制球体模型

	   glutSwapBuffers();//显示图形

   }

   void redisplay()
   {
	   GLint w = glutGet(GLUT_WINDOW_WIDTH);//获取当前窗口尺寸大小：单位：像素
       GLint h = glutGet(GLUT_WINDOW_HEIGHT);
	   if(w>h)
	       glViewport(0,0, h, h); //设置全局视口
	   else
		   glViewport(0,0, w, w); //设置全局视口

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
