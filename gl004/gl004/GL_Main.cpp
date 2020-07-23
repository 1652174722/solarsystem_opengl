#include"GL_Main.h"

const GLdouble Pi=3.1415926;
static int day =365; // day的变化：从0到359
static GLint Distance=149600000;;
static GLfloat angle = 0.0f; 
SolarSystem solarSYM;
//圆柱体的生成方法
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
	glBegin(GL_TRIANGLE_STRIP);//显示圆柱侧面
	for(int j=0;j<=slices;j++)
	{
		glVertex3f(arr[j][0],length/2.0,arr[j][1]);
		glVertex3f(arr[j][0],-length/2.0,arr[j][1]);
	}
	glEnd();
	glBegin(GL_TRIANGLE_FAN);//显示两个圆面
	glVertex3f(0.0,length/2.0,0.0);//中心点
	for(int j=0;j<=slices;j++)
		glVertex3f(arr[j][0],length/2.0,arr[j][1]);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0,-length/2.0,0.0);//中心点
	for(int j=0;j<=slices;j++)
		glVertex3f(arr[j][0],-length/2.0,arr[j][1]);
	glEnd();




	for(int i=0;i<=slices;i++)
		delete arr[i];
	delete arr;
}
void myDisplay(void)
{
     //清除缓冲区颜色
 /*   glClear(GL_COLOR_BUFFER_BIT);//清除函数
    //定义白色
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
    //圆点放坐标中心
    glLoadIdentity();  //对变换矩阵进行单位化
    //从哪个地方看eye_centre target  uper
    gluLookAt(0.0, 0.0, 5, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);


    glutWireTeapot(1.5);//线框茶壶函数
//	glutSolidTeapot(2);//线框茶壶函数
    //清除缓冲区刷新
//	glFlush();
*/

/*	//在四个视口显示图形
	glClearColor(0.0,0.0, 0.0,1.0); //设置清除颜色
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//清除函数	
	glColor3f(0.2,0.3, 1.0); //设置当前使用颜色
	GLint w = glutGet(GLUT_WINDOW_WIDTH);//获取当前窗口尺寸大小：单位：像素
    GLint h = glutGet(GLUT_WINDOW_HEIGHT);

	glViewport(0,0, w, h); //设置全局视口
	glMatrixMode(GL_PROJECTION);//当前矩阵为投影矩阵
    glLoadIdentity();//单位化
    gluPerspective(90, 1.0,0.0, 2000);//设置相机可视锥形体的大小
	gluLookAt(0.0, 0.0, 5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);//设置相机的位置与方向
	glMatrixMode(GL_MODELVIEW);//当前矩阵为模型矩阵
    glLoadIdentity();//单位化
	glBegin(GL_LINES);
	glVertex3f(-10000.0,0.0,0.0);
	glVertex3f(10000.0,0.0,0.0);
	glVertex3f(0.0,10000.0,0.0);
	glVertex3f(0.0,-10000.0,0.0);
	glEnd();



	GLint Min=min(w/2,h/2);
	glViewport(0,h/2, Min, Min); //设置第一个的视口
	glMatrixMode(GL_PROJECTION);//当前矩阵为投影矩阵
    glLoadIdentity();//单位化
    gluPerspective(90, 1.0,0.0, 2000);//设置相机可视锥形体的大小
	gluLookAt(0.0, 5.0, 5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);//设置相机的位置与方向
	glMatrixMode(GL_MODELVIEW);//当前矩阵为投影矩阵
    glLoadIdentity();//单位化
	WireCylinder(2,5,20,6);//绘制圆柱体

	glViewport(w/2,h/2, Min, Min); //设置第二个的视口
	glMatrixMode(GL_PROJECTION);//当前矩阵为投影矩阵
    glLoadIdentity();//单位化
    gluPerspective(90, 1.0,0.0, 2000);//设置相机可视锥形体的大小
	gluLookAt(0.0, 10.0, 10.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);//设置相机的位置与方向
	glMatrixMode(GL_MODELVIEW);//当前矩阵为投影矩阵
    glLoadIdentity();//单位化

	glTranslatef(0,0,0);//对模型的旋转操作
	glTranslatefv(v[3]);
	glRotatef(angle,0,0,0);
	glRotatefv(angle,v[3]);//物体绕向量v逆时针旋转angle
	glScalef(x_m,y_m,z_m);//物体分别在x,y,z方向拉伸x_m,y_m,z_m倍
	glScalefv(v[3]);

	WireCylinder(2,5,20,6);//绘制圆柱体

	glViewport(0,0, Min, Min); //设置第三个的视口
	glMatrixMode(GL_PROJECTION);//当前矩阵为投影矩阵
    glLoadIdentity();//单位化
    gluPerspective(90, 1.0,0.0, 2000);//设置相机可视锥形体的大小
	gluLookAt(0.0, 5.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);//设置相机的位置与方向
	glMatrixMode(GL_MODELVIEW);//当前矩阵为投影矩阵
    glLoadIdentity();//单位化
	glutWireTeapot(5);

	glViewport(w/2,0, Min, Min); //设置第四个的视口
	glMatrixMode(GL_PROJECTION);//当前矩阵为投影矩阵
    glLoadIdentity();//单位化
    gluPerspective(90, 1.0,0.0, 2000);//设置相机可视锥形体的大小
	gluLookAt(0.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);//设置相机的位置与方向
	glMatrixMode(GL_MODELVIEW);//当前矩阵为投影矩阵
    glLoadIdentity();//单位化
	glutWireTeapot(5);
	*/
	glClearColor(0.0,0.0, 0.0,1.0); //设置清除颜色
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//清除函数	
	glColor3f(0.2,0.3, 1.0); //设置当前使用颜色
	GLint w = glutGet(GLUT_WINDOW_WIDTH);//获取当前窗口尺寸大小：单位：像素
    GLint h = glutGet(GLUT_WINDOW_HEIGHT);

	glViewport(0,0, w, h); //设置全局视口
	glMatrixMode(GL_PROJECTION);//当前矩阵为投影矩阵
    glLoadIdentity();//单位化
    gluPerspective(90, 1.0,0.0, 2000);//设置相机可视锥形体的大小
	gluLookAt(0.0, 0.0, 5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);//设置相机的位置与方向
	glMatrixMode(GL_MODELVIEW);//当前矩阵为模型矩阵
    glLoadIdentity();//单位化
	glBegin(GL_LINES);
	glVertex3f(0.0,10000.0,0.0);
	glVertex3f(0.0,-10000.0,0.0);
	glEnd();


	GLdouble distance=50;
	if(w/2>h)
		glViewport(w/4-h/2,0,h,h);
	else
		glViewport(0,h/2-w/4,w/2,w/2);
	
	glMatrixMode(GL_PROJECTION);//当前矩阵为投影矩阵
    glLoadIdentity();//单位化
    gluPerspective(90, 1.0,0.0, 2000);//设置相机可视锥形体的大小
	gluLookAt(0.0, 0.0, distance, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);//设置相机的位置与方向
	glMatrixMode(GL_MODELVIEW);//当前矩阵为模型矩阵
    glLoadIdentity();//单位化
	glutWireTeapot(5);





	if(w/2>h)
		glViewport(w/2+w/4-h/2,0,h,h);
	else
		glViewport(w/2+0,h/2-w/4,w/2,w/2);
	
	glMatrixMode(GL_PROJECTION);//当前矩阵为投影矩阵
    glLoadIdentity();//单位化
//	glRotatef(-90,0.0,0.0,1.0);//对视图进行旋转，缩放，移动
    gluPerspective(90, 1.0,0.0, 2000);//设置相机可视锥形体的大小
	//对相机进行旋转，缩放，移动
	gluLookAt(0.0, 0.0, distance, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);//设置相机的位置与方向
	glMatrixMode(GL_MODELVIEW);//当前矩阵为模型矩阵
    glLoadIdentity();//单位化
//	glRotatef(180,0.0,0.0,1.0);//对模型进行旋转，缩放，移动
//	glScaled(2,2,2);
	glTranslatef(Distance-58,0,0);
	glutWireTeapot(5);
    glutSwapBuffers();
}
void myDisplay1(void){
    glClearColor(0.0,0.0, 0.0,1.0); //设置清除颜色：黑色
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//清除函数	
	glColor3f(0.0,1.0, 0.0); //设置当前使用颜色：绿色
	GLint w = glutGet(GLUT_WINDOW_WIDTH);//获取当前窗口尺寸大小：单位：像素
    GLint h = glutGet(GLUT_WINDOW_HEIGHT);
	glViewport(0,0, w, h); //设置全局视口
	//设置相机的位置
	glMatrixMode(GL_PROJECTION);//设置投影矩阵
	glLoadIdentity();//单位化
	gluPerspective(90,1.0,1.0,1000);//设置锥实体的尺寸大小
    gluLookAt(0,0,10,   0,0,0,   0,1,0);//设置相机的方位	
	glMatrixMode(GL_MODELVIEW);//设置投影矩阵
	glLoadIdentity();//单位化
	//glTranslatef(200,0,0);//将模型沿着x轴正向平移200
	


	GLfloat sun_light_position[4]={0,0,0,1.0};//定义光源的位置，若[3]==0,则光源位置无限远（方向性光或平行光）:此处为位置光，位置(0,0,0)
	GLfloat sun_light_ambient[4]={0,0,0,1.0};//为glLight*第 个参数，表示光线在环境中经过此反射后最后留在环境中的强度（颜色）用RRGA表示:此处最后为黑光
	GLfloat sun_light_diffuse[4]={1,1,1,1.0};//为为glLight*第 个参数，表示光线在环境中经过漫反射后所得到的光线强度，:此处为白光
	GLfloat sun_light_specular[4]={1,1,1,1.0};//                       表示光线在环境中经过镜面反射后所得到的光线强度：此处为白光
	glLightfv(GL_LIGHT0,GL_POSITION,sun_light_position);//配置light0号光源的属性
	glLightfv(GL_LIGHT0,GL_AMBIENT,sun_light_ambient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,sun_light_diffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR,sun_light_specular);
    
	glEnable(GL_LIGHT0);//开启light0号
	glEnable(GL_LIGHTING);//开始环境光照功能
	glEnable(GL_DEPTH_TEST);

	{//定制地球的材质并绘制地球
		GLfloat sun_mat_ambient[4]={0,0,0,1.0};//各种光线照射到该材质上，经过很多次反射后，最终遗留在环境 中的光线强度，
	    GLfloat sun_mat_diffuse[4]={1,0,0,1.0};//光线照射到该材质上经过漫反射形成的光线强度：红
	    GLfloat sun_mat_specular[4]={0,1,0,1.0};//光线照射到该材质上，经过镜面反射后形成的光线强度：蓝
	    GLfloat sun_mat_emission[4]={0.5,0.5,0.5,1.0};//表示材质的颜色：原理：将材质当成一种的光源，当光源强度很弱，不会对环境中其他物体产生影响
		GLfloat sun_mat_shininess=60;//镜面指数，	取值范围0-128，越小表示材质表面越粗糙，会产生分散的光斑；越大越光滑，会产生交集中的光斑
	    
	
		glMaterialfv(GL_FRONT,GL_AMBIENT,sun_mat_ambient);//设置材质的各种属性
		glMaterialfv(GL_FRONT,GL_DIFFUSE,sun_mat_diffuse);
		glMaterialfv(GL_FRONT,GL_SPECULAR,sun_mat_specular);
		glMaterialfv(GL_FRONT,GL_EMISSION,sun_mat_emission);
		glMaterialf(GL_FRONT,GL_SHININESS,sun_mat_shininess);		
	}
	

	glLoadIdentity();//单位化
//	glutSolidTeapot(300);//绘制茶壶，并设置好的材质赋予茶壶
//	glRotatef(90,0,1.0,0);//先平移再旋转
//	glTranslatef(3,0,0);
	
	glTranslatef(3,0,0);//先旋转再平移
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
	glClearColor(0.0,0.0,0.0,0);//可以当做环境背景颜色来设置
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //清理颜色和深度缓存      	// 创建透视效果视图      	
	glMatrixMode(GL_PROJECTION);   	
	glLoadIdentity();    	
	gluPerspective(80.0f, 1.0f, 1.0f, 20.0f);    	
	glMatrixMode(GL_MODELVIEW);   	
	glLoadIdentity();   	
	gluLookAt(0.0, 12.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);        	// 定义太阳光源，它是一种白色的光源   	
	{
    	GLfloat sun_light_position[] = {0.0f, 0.0f, 0.0f, 1.0f}; //光源的位置在世界坐标系圆心，齐次坐标形式		
		GLfloat sun_light_ambient[]   = {0.0f, 0.0f, 0.0f, 1.0f}; //RGBA模式的环境光，为0		
		GLfloat sun_light_diffuse[]   = {1.0f, 1.0f, 1.0f, 1.0f}; //RGBA模式的漫反射光，全白光		
		GLfloat sun_light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};  //RGBA模式下的镜面光 ，全白光		
		glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);     		
		glLightfv(GL_LIGHT0, GL_AMBIENT,   sun_light_ambient);  
		glLightfv(GL_LIGHT0, GL_DIFFUSE,   sun_light_diffuse);   		
		glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);      		//开启灯光		
		glEnable(GL_LIGHT0);    		
		glEnable(GL_LIGHTING);   		
		glEnable(GL_DEPTH_TEST);  	
	}
	{       		
		GLfloat sun_mat_ambient[]   = {0.0f, 0.0f, 0.0f, 1.0f};  //定义材质的环境光颜色，为0		
		GLfloat sun_mat_diffuse[]   = {0.0f, 0.0f, 0.0f, 1.0f};  //定义材质的漫反射光颜色，为0		
		GLfloat sun_mat_specular[] = {0.0f, 0.0f, 0.0f, 1.0f};   //定义材质的镜面反射光颜色，为0		
		GLfloat sun_mat_emission[] = {1.0f, 1.0f, 1.0f, 1.0f};   //定义材质的辐射广颜色，为偏红色		
		GLfloat sun_mat_shininess   = 0.0f;        		
		glMaterialfv(GL_FRONT, GL_AMBIENT,    sun_mat_ambient);    		
		glMaterialfv(GL_FRONT, GL_DIFFUSE,    sun_mat_diffuse);   		
		glMaterialfv(GL_FRONT, GL_SPECULAR,   sun_mat_specular);    		
		glMaterialfv(GL_FRONT, GL_EMISSION,   sun_mat_emission);   		
		glMaterialf (GL_FRONT, GL_SHININESS, sun_mat_shininess);    		
		glutSolidSphere(3.0, 40, 32);    	
	}
	{        		
		GLfloat earth_mat_ambient[]   = {0.0, 1.0, 0.0, 1.0};  //定义材质的环境光颜色，绿色	
		GLfloat earth_mat_diffuse[]   = {0.0, 0.0, 1.0, 1.0};  //定义材质的漫反射光颜色，蓝色		
		GLfloat earth_mat_specular[] = {1.0, 0.0, 0.0, 1.0};   //定义材质的镜面反射光颜色，红色		
		GLfloat earth_mat_emission[] = {0.0, 0.0, 0.0, 1.0};   //定义材质的辐射光颜色，为0		
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
//窗口改变时回调函数调用的函数:窗口第一次创建时，也会调用此函数:
void reshape(int w, int h) {
	GLint width = glutGet(GLUT_WINDOW_WIDTH);
    GLint height = glutGet(GLUT_WINDOW_HEIGHT);
    //定义视口大小
//	if(w>h)
//       glViewport(0, 0, (GLsizei) h, (GLsizei) h); 
//	else
//	   glViewport(0, 0, (GLsizei) w, (GLsizei) w); 
//	glViewport(0, 0, width/2, height/2); 
    //投影显示
    glMatrixMode(GL_PROJECTION);//当前矩阵为投影矩阵
    //坐标原点在屏幕中心
    glLoadIdentity();
    //操作模型视景
    gluPerspective(90, 1.0 ,0.0, 2000);//设置锥形体的大小//设置照片的尺寸大小
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
	//mercury 水星，Venus:金星 Mars火星， Jupiter  :木星
	//Saturm:土星，//Uranus:天王星，Neptune:海王星 Pluto:冥王星
	GLfloat RGBA[4]={1.0,0.0,0.0,1.0};//红色，太阳:color[4],selfPeriod,redius,revolutionPeriods,
	//GrevolutionRedius,father,currRevaltionAngle,currSelfAngle
	Planet sun(RGBA,0,100,0,0,NULL,0,0);
	sun.SetModelslices_stack(20,20);//太阳


	RGBA[0]=0.0;
	RGBA[2]=1.0;//蓝色
	Planet earth(RGBA,0,50,360,300,&sun,0,0);
	earth.SetModelslices_stack(20,20);
	Planet earth1(RGBA,0,30,360,200,&sun,180,0);
	earth1.SetModelslices_stack(20,20);
	RGBA[0]=0.1;
	RGBA[1]=0.1;
	RGBA[2]=0.1;//白色
	Planet moon(RGBA,0,20,30,100,&earth,0,0);
	moon.SetModelslices_stack(20,20);
	solarSYM.AddPlanet(&sun);
	solarSYM.AddPlanet(&earth);
	solarSYM.AddPlanet(&earth1);
	solarSYM.AddPlanet(&moon);
	//初始化
    glutInit(&argc, argv);
    //设置显示模式
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    //初始化窗口大小
    glutInitWindowSize(500, 500); 
    //定义左上角窗口位置
    glutInitWindowPosition(100, 100);
    //创建窗口
    glutCreateWindow(argv[0]);
    //清除颜色缓冲区
    glClearColor(0.0, 0.0, 0.0, 0.0); 
    //显示函数
    glutDisplayFunc(myDisplay3);
    //窗口大小改变时的响应
//    glutReshapeFunc(solarSYM.redisplay);
	glutIdleFunc(myIdle3);
	glutKeyboardFunc(myResponseFunction);
	glutSpecialFunc(myResponseFunction_special);
    //循环
    glutMainLoop();
    return 0;

}
