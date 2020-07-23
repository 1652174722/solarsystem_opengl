#include"GL_Main.h"

const GLdouble Pi=3.1415926;
static int day =365; // day�ı仯����0��359
static GLint Distance=149600000;;
static GLfloat angle = 0.0f; 
SolarSystem solarSYM;
//Բ��������ɷ���
void WireCylinder(GLdouble radius,GLdouble length,GLint slices,GLint stacks)//
{
    
	GLdouble deta_y=length/stacks;
	GLdouble deta_alfa=2.0*Pi/slices;
	GLdouble alfa;
	GLdouble y;
	GLdouble **arr=new GLdouble*[slices+1];
	for(int i=0;i<=slices;i++)
		arr[i]=new GLdouble[2];//x,z
	for(int i=0;i<=slices;i++)
    {
		alfa=i*deta_alfa;
		arr[i][0]=radius*cos(alfa);
		arr[i][1]=radius*sin(alfa);
    }
	for(int i=0;i<=stacks;i++)
	{
		glBegin(GL_LINE_LOOP);//n n+1,n+2
		y=length/2.0-i*deta_y;
		for(int j=0;j<slices;j++)
		{
			glVertex3f(arr[j][0],y,arr[j][1]);
		}
		glEnd();
	}
	glBegin(GL_LINES);//n n+1,n+2
	for(int j=0;j<slices;j++)
	{
		glVertex3f(arr[j][0],length/2.0,arr[j][1]);
		glVertex3f(arr[j][0],-length/2.0,arr[j][1]);
	}
	glEnd();
	for(int i=0;i<=slices;i++)
		delete arr[i];
	delete arr;
}
void SolidCylinder(GLdouble radius,GLdouble length,GLint slices,GLint stacks)//
{
    
	GLdouble deta_y=length/stacks;
	GLdouble deta_alfa=2.0*Pi/slices;
	GLdouble alfa;
	GLdouble **arr=new GLdouble*[slices+1];
	for(int i=0;i<=slices;i++)
		arr[i]=new GLdouble[2];//x,z
	for(int i=0;i<=slices;i++)
    {
		alfa=i*deta_alfa;
		arr[i][0]=radius*cos(alfa);
		arr[i][1]=radius*sin(alfa);
    }
	glBegin(GL_TRIANGLE_STRIP);//��ʾԲ������
	for(int j=0;j<=slices;j++)
	{
		glVertex3f(arr[j][0],length/2.0,arr[j][1]);
		glVertex3f(arr[j][0],-length/2.0,arr[j][1]);
	}
	glEnd();
	glBegin(GL_TRIANGLE_FAN);//��ʾ����Բ��
	glVertex3f(0.0,length/2.0,0.0);//���ĵ�
	for(int j=0;j<=slices;j++)
		glVertex3f(arr[j][0],length/2.0,arr[j][1]);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0,-length/2.0,0.0);//���ĵ�
	for(int j=0;j<=slices;j++)
		glVertex3f(arr[j][0],-length/2.0,arr[j][1]);
	glEnd();




	for(int i=0;i<=slices;i++)
		delete arr[i];
	delete arr;
}
void myDisplay(void)
{
     //�����������ɫ
 /*   glClear(GL_COLOR_BUFFER_BIT);//�������
    //�����ɫ
    glColor3f(0.2,0.3, 1.0); 
	GLint width = glutGet(GLUT_WINDOW_WIDTH);
    GLint height = glutGet(GLUT_WINDOW_HEIGHT);
	glViewport(0, 0, width, height); 
	glBegin(GL_LINES);
	glVertex3f(-30,0.0,0.0);
	glVertex3f(1.0,0.0,0.0);
	glVertex3f(0.0,1.0,0.0);
	glVertex3f(0.0,-1.0,0.0);
	glEnd();

	if(width>height)
       glViewport(0, 0, height, height); 
	else
	   glViewport(0, 0, width,  width); 
    //Բ�����������
    glLoadIdentity();  //�Ա任������е�λ��
    //���ĸ��ط���eye_centre target  uper
    gluLookAt(0.0, 0.0, 5, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);


    glutWireTeapot(1.5);//�߿�������
//	glutSolidTeapot(2);//�߿�������
    //���������ˢ��
//	glFlush();
*/

/*	//���ĸ��ӿ���ʾͼ��
	glClearColor(0.0,0.0, 0.0,1.0); //���������ɫ
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//�������	
	glColor3f(0.2,0.3, 1.0); //���õ�ǰʹ����ɫ
	GLint w = glutGet(GLUT_WINDOW_WIDTH);//��ȡ��ǰ���ڳߴ��С����λ������
    GLint h = glutGet(GLUT_WINDOW_HEIGHT);

	glViewport(0,0, w, h); //����ȫ���ӿ�
	glMatrixMode(GL_PROJECTION);//��ǰ����ΪͶӰ����
    glLoadIdentity();//��λ��
    gluPerspective(90, 1.0,0.0, 2000);//�����������׶����Ĵ�С
	gluLookAt(0.0, 0.0, 5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);//���������λ���뷽��
	glMatrixMode(GL_MODELVIEW);//��ǰ����Ϊģ�;���
    glLoadIdentity();//��λ��
	glBegin(GL_LINES);
	glVertex3f(-10000.0,0.0,0.0);
	glVertex3f(10000.0,0.0,0.0);
	glVertex3f(0.0,10000.0,0.0);
	glVertex3f(0.0,-10000.0,0.0);
	glEnd();



	GLint Min=min(w/2,h/2);
	glViewport(0,h/2, Min, Min); //���õ�һ�����ӿ�
	glMatrixMode(GL_PROJECTION);//��ǰ����ΪͶӰ����
    glLoadIdentity();//��λ��
    gluPerspective(90, 1.0,0.0, 2000);//�����������׶����Ĵ�С
	gluLookAt(0.0, 5.0, 5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);//���������λ���뷽��
	glMatrixMode(GL_MODELVIEW);//��ǰ����ΪͶӰ����
    glLoadIdentity();//��λ��
	WireCylinder(2,5,20,6);//����Բ����

	glViewport(w/2,h/2, Min, Min); //���õڶ������ӿ�
	glMatrixMode(GL_PROJECTION);//��ǰ����ΪͶӰ����
    glLoadIdentity();//��λ��
    gluPerspective(90, 1.0,0.0, 2000);//�����������׶����Ĵ�С
	gluLookAt(0.0, 10.0, 10.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);//���������λ���뷽��
	glMatrixMode(GL_MODELVIEW);//��ǰ����ΪͶӰ����
    glLoadIdentity();//��λ��

	glTranslatef(0,0,0);//��ģ�͵���ת����
	glTranslatefv(v[3]);
	glRotatef(angle,0,0,0);
	glRotatefv(angle,v[3]);//����������v��ʱ����תangle
	glScalef(x_m,y_m,z_m);//����ֱ���x,y,z��������x_m,y_m,z_m��
	glScalefv(v[3]);

	WireCylinder(2,5,20,6);//����Բ����

	glViewport(0,0, Min, Min); //���õ��������ӿ�
	glMatrixMode(GL_PROJECTION);//��ǰ����ΪͶӰ����
    glLoadIdentity();//��λ��
    gluPerspective(90, 1.0,0.0, 2000);//�����������׶����Ĵ�С
	gluLookAt(0.0, 5.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);//���������λ���뷽��
	glMatrixMode(GL_MODELVIEW);//��ǰ����ΪͶӰ����
    glLoadIdentity();//��λ��
	glutWireTeapot(5);

	glViewport(w/2,0, Min, Min); //���õ��ĸ����ӿ�
	glMatrixMode(GL_PROJECTION);//��ǰ����ΪͶӰ����
    glLoadIdentity();//��λ��
    gluPerspective(90, 1.0,0.0, 2000);//�����������׶����Ĵ�С
	gluLookAt(0.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);//���������λ���뷽��
	glMatrixMode(GL_MODELVIEW);//��ǰ����ΪͶӰ����
    glLoadIdentity();//��λ��
	glutWireTeapot(5);
	*/
	glClearColor(0.0,0.0, 0.0,1.0); //���������ɫ
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//�������	
	glColor3f(0.2,0.3, 1.0); //���õ�ǰʹ����ɫ
	GLint w = glutGet(GLUT_WINDOW_WIDTH);//��ȡ��ǰ���ڳߴ��С����λ������
    GLint h = glutGet(GLUT_WINDOW_HEIGHT);

	glViewport(0,0, w, h); //����ȫ���ӿ�
	glMatrixMode(GL_PROJECTION);//��ǰ����ΪͶӰ����
    glLoadIdentity();//��λ��
    gluPerspective(90, 1.0,0.0, 2000);//�����������׶����Ĵ�С
	gluLookAt(0.0, 0.0, 5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);//���������λ���뷽��
	glMatrixMode(GL_MODELVIEW);//��ǰ����Ϊģ�;���
    glLoadIdentity();//��λ��
	glBegin(GL_LINES);
	glVertex3f(0.0,10000.0,0.0);
	glVertex3f(0.0,-10000.0,0.0);
	glEnd();


	GLdouble distance=50;
	if(w/2>h)
		glViewport(w/4-h/2,0,h,h);
	else
		glViewport(0,h/2-w/4,w/2,w/2);
	
	glMatrixMode(GL_PROJECTION);//��ǰ����ΪͶӰ����
    glLoadIdentity();//��λ��
    gluPerspective(90, 1.0,0.0, 2000);//�����������׶����Ĵ�С
	gluLookAt(0.0, 0.0, distance, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);//���������λ���뷽��
	glMatrixMode(GL_MODELVIEW);//��ǰ����Ϊģ�;���
    glLoadIdentity();//��λ��
	glutWireTeapot(5);





	if(w/2>h)
		glViewport(w/2+w/4-h/2,0,h,h);
	else
		glViewport(w/2+0,h/2-w/4,w/2,w/2);
	
	glMatrixMode(GL_PROJECTION);//��ǰ����ΪͶӰ����
    glLoadIdentity();//��λ��
//	glRotatef(-90,0.0,0.0,1.0);//����ͼ������ת�����ţ��ƶ�
    gluPerspective(90, 1.0,0.0, 2000);//�����������׶����Ĵ�С
	//�����������ת�����ţ��ƶ�
	gluLookAt(0.0, 0.0, distance, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);//���������λ���뷽��
	glMatrixMode(GL_MODELVIEW);//��ǰ����Ϊģ�;���
    glLoadIdentity();//��λ��
//	glRotatef(180,0.0,0.0,1.0);//��ģ�ͽ�����ת�����ţ��ƶ�
//	glScaled(2,2,2);
	glTranslatef(Distance-58,0,0);
	glutWireTeapot(5);
    glutSwapBuffers();
}
void myDisplay1(void){
    glClearColor(0.0,0.0, 0.0,1.0); //���������ɫ����ɫ
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//�������	
	glColor3f(0.0,1.0, 0.0); //���õ�ǰʹ����ɫ����ɫ
	GLint w = glutGet(GLUT_WINDOW_WIDTH);//��ȡ��ǰ���ڳߴ��С����λ������
    GLint h = glutGet(GLUT_WINDOW_HEIGHT);
	glViewport(0,0, w, h); //����ȫ���ӿ�
	//���������λ��
	glMatrixMode(GL_PROJECTION);//����ͶӰ����
	glLoadIdentity();//��λ��
	gluPerspective(90,1.0,1.0,1000);//����׶ʵ��ĳߴ��С
    gluLookAt(0,0,10,   0,0,0,   0,1,0);//��������ķ�λ	
	glMatrixMode(GL_MODELVIEW);//����ͶӰ����
	glLoadIdentity();//��λ��
	//glTranslatef(200,0,0);//��ģ������x������ƽ��200
	


	GLfloat sun_light_position[4]={0,0,0,1.0};//�����Դ��λ�ã���[3]==0,���Դλ������Զ�������Թ��ƽ�й⣩:�˴�Ϊλ�ù⣬λ��(0,0,0)
	GLfloat sun_light_ambient[4]={0,0,0,1.0};//ΪglLight*�� ����������ʾ�����ڻ����о����˷����������ڻ����е�ǿ�ȣ���ɫ����RRGA��ʾ:�˴����Ϊ�ڹ�
	GLfloat sun_light_diffuse[4]={1,1,1,1.0};//ΪΪglLight*�� ����������ʾ�����ڻ����о�������������õ��Ĺ���ǿ�ȣ�:�˴�Ϊ�׹�
	GLfloat sun_light_specular[4]={1,1,1,1.0};//                       ��ʾ�����ڻ����о������淴������õ��Ĺ���ǿ�ȣ��˴�Ϊ�׹�
	glLightfv(GL_LIGHT0,GL_POSITION,sun_light_position);//����light0�Ź�Դ������
	glLightfv(GL_LIGHT0,GL_AMBIENT,sun_light_ambient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,sun_light_diffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR,sun_light_specular);
    
	glEnable(GL_LIGHT0);//����light0��
	glEnable(GL_LIGHTING);//��ʼ�������չ���
	glEnable(GL_DEPTH_TEST);

	{//���Ƶ���Ĳ��ʲ����Ƶ���
		GLfloat sun_mat_ambient[4]={0,0,0,1.0};//���ֹ������䵽�ò����ϣ������ܶ�η�������������ڻ��� �еĹ���ǿ�ȣ�
	    GLfloat sun_mat_diffuse[4]={1,0,0,1.0};//�������䵽�ò����Ͼ����������γɵĹ���ǿ�ȣ���
	    GLfloat sun_mat_specular[4]={0,1,0,1.0};//�������䵽�ò����ϣ��������淴����γɵĹ���ǿ�ȣ���
	    GLfloat sun_mat_emission[4]={0.5,0.5,0.5,1.0};//��ʾ���ʵ���ɫ��ԭ�������ʵ���һ�ֵĹ�Դ������Դǿ�Ⱥ���������Ի����������������Ӱ��
		GLfloat sun_mat_shininess=60;//����ָ����	ȡֵ��Χ0-128��ԽС��ʾ���ʱ���Խ�ֲڣ��������ɢ�Ĺ�ߣ�Խ��Խ�⻬������������еĹ��
	    
	
		glMaterialfv(GL_FRONT,GL_AMBIENT,sun_mat_ambient);//���ò��ʵĸ�������
		glMaterialfv(GL_FRONT,GL_DIFFUSE,sun_mat_diffuse);
		glMaterialfv(GL_FRONT,GL_SPECULAR,sun_mat_specular);
		glMaterialfv(GL_FRONT,GL_EMISSION,sun_mat_emission);
		glMaterialf(GL_FRONT,GL_SHININESS,sun_mat_shininess);		
	}
	

	glLoadIdentity();//��λ��
//	glutSolidTeapot(300);//���Ʋ���������úõĲ��ʸ�����
//	glRotatef(90,0,1.0,0);//��ƽ������ת
//	glTranslatef(3,0,0);
	
	glTranslatef(3,0,0);//����ת��ƽ��
	glRotatef(90,0,1.0,0);
	
	GLfloat mat[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, mat);
	cout<<mat[0]<<"  "<<mat[4]<<"  "<<mat[8]<<"  "<<mat[12]<<endl;
	cout<<mat[1]<<"  "<<mat[5]<<"  "<<mat[9]<<"  "<<mat[13]<<endl;
	cout<<mat[2]<<"  "<<mat[6]<<"  "<<mat[10]<<"  "<<mat[14]<<endl;
	cout<<mat[3]<<"  "<<mat[7]<<"  "<<mat[11]<<"  "<<mat[15]<<endl;
	glutSolidSphere(2, 40, 32);  
	glutSwapBuffers();
	
}
void myDisplay2(void)
{
	glClearColor(0.0,0.0,0.0,0);//���Ե�������������ɫ������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //������ɫ����Ȼ���      	// ����͸��Ч����ͼ      	
	glMatrixMode(GL_PROJECTION);   	
	glLoadIdentity();    	
	gluPerspective(80.0f, 1.0f, 1.0f, 20.0f);    	
	glMatrixMode(GL_MODELVIEW);   	
	glLoadIdentity();   	
	gluLookAt(0.0, 12.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);        	// ����̫����Դ������һ�ְ�ɫ�Ĺ�Դ   	
	{
    	GLfloat sun_light_position[] = {0.0f, 0.0f, 0.0f, 1.0f}; //��Դ��λ������������ϵԲ�ģ����������ʽ		
		GLfloat sun_light_ambient[]   = {0.0f, 0.0f, 0.0f, 1.0f}; //RGBAģʽ�Ļ����⣬Ϊ0		
		GLfloat sun_light_diffuse[]   = {1.0f, 1.0f, 1.0f, 1.0f}; //RGBAģʽ��������⣬ȫ�׹�		
		GLfloat sun_light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};  //RGBAģʽ�µľ���� ��ȫ�׹�		
		glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);     		
		glLightfv(GL_LIGHT0, GL_AMBIENT,   sun_light_ambient);  
		glLightfv(GL_LIGHT0, GL_DIFFUSE,   sun_light_diffuse);   		
		glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);      		//�����ƹ�		
		glEnable(GL_LIGHT0);    		
		glEnable(GL_LIGHTING);   		
		glEnable(GL_DEPTH_TEST);  	
	}
	{       		
		GLfloat sun_mat_ambient[]   = {0.0f, 0.0f, 0.0f, 1.0f};  //������ʵĻ�������ɫ��Ϊ0		
		GLfloat sun_mat_diffuse[]   = {0.0f, 0.0f, 0.0f, 1.0f};  //������ʵ����������ɫ��Ϊ0		
		GLfloat sun_mat_specular[] = {0.0f, 0.0f, 0.0f, 1.0f};   //������ʵľ��淴�����ɫ��Ϊ0		
		GLfloat sun_mat_emission[] = {1.0f, 1.0f, 1.0f, 1.0f};   //������ʵķ������ɫ��Ϊƫ��ɫ		
		GLfloat sun_mat_shininess   = 0.0f;        		
		glMaterialfv(GL_FRONT, GL_AMBIENT,    sun_mat_ambient);    		
		glMaterialfv(GL_FRONT, GL_DIFFUSE,    sun_mat_diffuse);   		
		glMaterialfv(GL_FRONT, GL_SPECULAR,   sun_mat_specular);    		
		glMaterialfv(GL_FRONT, GL_EMISSION,   sun_mat_emission);   		
		glMaterialf (GL_FRONT, GL_SHININESS, sun_mat_shininess);    		
		glutSolidSphere(3.0, 40, 32);    	
	}
	{        		
		GLfloat earth_mat_ambient[]   = {0.0, 1.0, 0.0, 1.0};  //������ʵĻ�������ɫ����ɫ	
		GLfloat earth_mat_diffuse[]   = {0.0, 0.0, 1.0, 1.0};  //������ʵ����������ɫ����ɫ		
		GLfloat earth_mat_specular[] = {1.0, 0.0, 0.0, 1.0};   //������ʵľ��淴�����ɫ����ɫ		
		GLfloat earth_mat_emission[] = {0.0, 0.0, 0.0, 1.0};   //������ʵķ������ɫ��Ϊ0		
		GLfloat earth_mat_shininess   = 30.0f;       		
		glMaterialfv(GL_FRONT, GL_AMBIENT,    earth_mat_ambient);   		
		glMaterialfv(GL_FRONT, GL_DIFFUSE,    earth_mat_diffuse);    		
		glMaterialfv(GL_FRONT, GL_SPECULAR,   earth_mat_specular);     		
		glMaterialfv(GL_FRONT, GL_EMISSION,   earth_mat_emission);   		
		glMaterialf (GL_FRONT, GL_SHININESS, earth_mat_shininess);    		
		glRotatef(angle, 0.0f, -1.0f, 0.0f);       		
		glTranslatef(7.0f, 0.0f, 0.0f);        		
		glutSolidSphere(3.0, 40, 32);     	
	}    	
//	_sleep(10);
	glutSwapBuffers();
}


void myDisplay3(void)
{
	solarSYM.display();
}



void myIdle1(void)
{
	Distance++;
	if(Distance>115)
		Distance=0;
	_sleep(100);
	myDisplay();
}
void myIdle2()
{
	angle += 1.0f; 
	if( angle >= 360.0f )    
	angle = 0.0f; 
	myDisplay2();
}
void myIdle3()
{
	_sleep(100);
	solarSYM.display();
}
//���ڸı�ʱ�ص��������õĺ���:���ڵ�һ�δ���ʱ��Ҳ����ô˺���:
void reshape(int w, int h) {
	GLint width = glutGet(GLUT_WINDOW_WIDTH);
    GLint height = glutGet(GLUT_WINDOW_HEIGHT);
    //�����ӿڴ�С
//	if(w>h)
//       glViewport(0, 0, (GLsizei) h, (GLsizei) h); 
//	else
//	   glViewport(0, 0, (GLsizei) w, (GLsizei) w); 
//	glViewport(0, 0, width/2, height/2); 
    //ͶӰ��ʾ
    glMatrixMode(GL_PROJECTION);//��ǰ����ΪͶӰ����
    //����ԭ������Ļ����
    glLoadIdentity();
    //����ģ���Ӿ�
    gluPerspective(90, 1.0 ,0.0, 2000);//����׶����Ĵ�С//������Ƭ�ĳߴ��С
    glMatrixMode(GL_MODELVIEW);

}

void  myResponseFunction(unsigned char key, int x, int y)
{
	solarSYM.ResponseFunction(key,x,y);
}

void myResponseFunction_special(int key, int x, int y)
{

	solarSYM.ResponseFunction_special(key,x,y);
}
int main(int argc, char* argv[])
{
	//mercury ˮ�ǣ�Venus:���� Mars���ǣ� Jupiter  :ľ��
	//Saturm:���ǣ�//Uranus:�����ǣ�Neptune:������ Pluto:ڤ����
	GLfloat RGBA[4]={1.0,0.0,0.0,1.0};//��ɫ��̫��:color[4],selfPeriod,redius,revolutionPeriods,
	//GrevolutionRedius,father,currRevaltionAngle,currSelfAngle
	Planet sun(RGBA,0,100,0,0,NULL,0,0);
	sun.SetModelslices_stack(20,20);//̫��


	RGBA[0]=0.0;
	RGBA[2]=1.0;//��ɫ
	Planet earth(RGBA,0,50,360,300,&sun,0,0);
	earth.SetModelslices_stack(20,20);
	Planet earth1(RGBA,0,30,360,200,&sun,180,0);
	earth1.SetModelslices_stack(20,20);
	RGBA[0]=0.1;
	RGBA[1]=0.1;
	RGBA[2]=0.1;//��ɫ
	Planet moon(RGBA,0,20,30,100,&earth,0,0);
	moon.SetModelslices_stack(20,20);
	solarSYM.AddPlanet(&sun);
	solarSYM.AddPlanet(&earth);
	solarSYM.AddPlanet(&earth1);
	solarSYM.AddPlanet(&moon);
	//��ʼ��
    glutInit(&argc, argv);
    //������ʾģʽ
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    //��ʼ�����ڴ�С
    glutInitWindowSize(500, 500); 
    //�������ϽǴ���λ��
    glutInitWindowPosition(100, 100);
    //��������
    glutCreateWindow(argv[0]);
    //�����ɫ������
    glClearColor(0.0, 0.0, 0.0, 0.0); 
    //��ʾ����
    glutDisplayFunc(myDisplay3);
    //���ڴ�С�ı�ʱ����Ӧ
//    glutReshapeFunc(solarSYM.redisplay);
	glutIdleFunc(myIdle3);
	glutKeyboardFunc(myResponseFunction);
	glutSpecialFunc(myResponseFunction_special);
    //ѭ��
    glutMainLoop();
    return 0;

}
