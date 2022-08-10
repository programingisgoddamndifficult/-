#include "Operate.h"
#include"necessaryFile.h"
#include"BasicWidget.h"
Operate::Operate()
{
	initMeun();
	initBook();
	initBackPack();
	initMap();
}

void Operate::run()
{
	op = menu();//��ȡ�˵�����ֵ
	Window::beginDraw();
	while (1)
	{
		Window::clear();
		settextstyle(20, 0, "����");
		drawBackground();
		if (Window::hasMsg())
		{
			m_msg = Window::getMsg();
			switch (m_msg.message)
			{
			case WM_KEYDOWN: //��������
				if (m_msg.vkcode == VK_ESCAPE)//��ESC�˳�����������������
				{
					op = Menu;
				}break;
			default:
				//������
				break;
			}
		}
		switch (op)
		{
		case Menu:
			op = menu(); break;
		case PlayerInfo:
			ShowPlayerInfo(); 
			me.ba = 0;//����ӵ�е���Ŀ
			check_bag(); break;
		case Map:
			ShowMap(); break;
		case Elf:
			ShowElf(); break;
		case SEARCH:
			Search(); break;
		case BOSS:
			ShowBoss(); break;
		}
		Window::flushDraw();		
	}
	Window::endDraw();
}

int Operate::menu()
{
	for (int i = 0; i < menu_btns.size(); i++)
	{
		menu_btns[i]->show();
		menu_btns[i]->changeColor(m_msg);
		//����ť���
		if (menu_btns[i]->isClicked())
		{
			return i+1;
		}
	}
	return Menu;
}

int Operate::book()
{
	for (int i = 0; i < 9; i++)
	{
		book_btns[i+9*m_curPage]->show();
		book_btns[i+9*m_curPage]->changeColor(m_msg);
		//����ť���
		if (book_btns[i+9*m_curPage]->isClicked())
		{
			temp = i + 9 * m_curPage;
			flag = 0;
			return i + 9 * m_curPage;
		}
	}
	return Elf;
}

void Operate::book_sec()
{
	book_btns_sec[temp]->show();
	book_btns_sec[temp]->changeColor(m_msg);
	if (book_btns_sec[temp]->isClicked())
	{
		flag = 1;
	}
}

void Operate::book_thr()
{
	if (elf[temp]->condition == 'Y')
	{
		book_btns_thr[temp]->show();
		book_btns_thr[temp]->changeColor(m_msg);
		if (book_btns_thr[temp]->isClicked())
		{
			elf[temp]->condition = 'N';
		}
	}
}

void Operate::map_catch()
{
	m_catch->show();
	m_catch->changeColor(m_msg);
	if (m_catch->isClicked() && Timer(500))
	{
		ca = rand() % elf.size();
		switch (elf[ca]->condition)
		{
		case 'N':
			boss_flag = 0;
			if (elf[ca]->level - me.level < 2)
				catch_flag = 1; 
			else
				catch_flag = 2; break;
		case 'Y':
		catch_flag = 3;
		//�������Boss
		for (int i = 0; i < 9; i++)
		{
			if (boss[i]->feature == elf[ca]->feature)
			{
				int ran = rand() % 10 + 1;
				if (ran >= (boss[i]->rate * 10))
				{
					boss[i]->condition = 'Y';
					boss_flag = 1;
					boss_index = i;
				}
			}
		}break; 
		default:break;
		}
		
	}
}

void Operate::drawPageTurnButton()
{
	m_prevBtn->move(Window::Width()/2, Window::Height()-40);
	m_nextBtn->move(m_prevBtn->x() + m_prevBtn->width(), m_prevBtn->y());
	m_prevBtn->show();
	m_nextBtn->show();
	m_prevBtn->changeColor(m_msg);
	m_nextBtn->changeColor(m_msg);
	//����ť���
	if (m_prevBtn->isClicked())
	{
		if (m_curPage != 0)
			m_curPage--;
	}
	if (m_nextBtn->isClicked())
	{
		if (m_curPage != m_maxPage)
			m_curPage++;
	}
}

void Operate::info_boss()
{
	m_boss->move(Window::Width() / 2 - t_width * 9, Window::Height() / 2 + t_height);
	m_boss->show();
	m_boss->changeColor(m_msg);
	if (m_boss->isClicked())
	{
		op = BOSS;
	}
}

void Operate::check_bag()
{
	for (int i = 0; i < elf.size(); i++)
	{
		if (elf[i]->condition == 'Y')
			me.ba++;
	}
}

void Operate::initMeun()
{
	loadimage(&bk, "./Images/background.jpeg", Window::Width(), Window::Height());
	settextstyle(t_height, t_width, "����");
	//�˵�ҳ�水ť��ʼ��
	menu_btns.push_back(new PushButton("��ͼ"));
	menu_btns.push_back(new PushButton("�����Ϣ"));
	menu_btns.push_back(new PushButton("������ͼ��"));
	menu_btns.push_back(new PushButton("����"));
	for (int i = 0; i < menu_btns.size(); i++)
	{
		menu_btns[i]->setFixedSize(250, 50);
		int bx = (Window::Width() - menu_btns[i]->width()) / 2;
		int vspace = (Window::Height() - menu_btns.size()*menu_btns[i]->height()) / 2;
		int by = vspace + i * menu_btns[i]->height();
		menu_btns[i]->move(bx, by);
	}
}

void Operate::initBook()
{
	loadimage(&bookbk, "./Images/bookbk.jpg", Window::Width(), Window::Height());
	//��ҳ����
	m_prevBtn = new PushButton("��һҳ");
	m_nextBtn = new PushButton("��һҳ");
	
	elf.push_back(new Monster("Ƥ����","��"));//���ؿڴ�����
	loadimage(&(elf[0]->img), "./Images/Pikachu.png", Window::Width() / 2, Window::Height()*0.8);
	book_btns.push_back(new PushButton("Ƥ����"));//����ͼ����ť
	book_btns_thr.push_back(new PushButton("����"));//���ط�����ť
	elf.push_back(new Monster("��������","��"));
	loadimage(&(elf[1]->img), "./Images/Bulbasaur.png", Window::Width() / 2, Window::Height()*0.8);
	book_btns.push_back(new PushButton("��������"));
	book_btns_thr.push_back(new PushButton("����"));
	elf.push_back(new Monster("С����","��"));
	loadimage(&(elf[2]->img), "./Images/Charmander.png", Window::Width() / 2, Window::Height()*0.7);
	book_btns.push_back(new PushButton("С����"));
	book_btns_thr.push_back(new PushButton("����"));
	elf.push_back(new Monster("�����","ˮ"));
	loadimage(&(elf[3]->img), "./Images/Squirtle.png", Window::Width() / 2, Window::Height()*0.7);
	book_btns.push_back(new PushButton("�����"));
	book_btns_thr.push_back(new PushButton("����"));
	elf.push_back(new Monster("ƤƤ", "����"));
	loadimage(&(elf[4]->img), "./Images/Clefairy.png", Window::Width() / 2, Window::Height()*0.7);
	book_btns.push_back(new PushButton("ƤƤ"));
	book_btns_thr.push_back(new PushButton("����"));
	elf.push_back(new Monster("��β","��"));
	loadimage(&(elf[5]->img), "./Images/Vulpix.png", Window::Width() / 2, Window::Height()*0.7);
	book_btns.push_back(new PushButton("��β"));
	book_btns_thr.push_back(new PushButton("����"));
	elf.push_back(new Monster("�ֶ�"));
	loadimage(&(elf[6]->img), "./Images/Jigglypuff.png", Window::Width() / 2, Window::Height()*0.7);
	book_btns.push_back(new PushButton("�ֶ�"));
	book_btns_thr.push_back(new PushButton("����"));
	elf.push_back(new Monster("�ɴ�Ѽ","ˮ"));
	loadimage(&(elf[7]->img), "./Images/Psyduck.png", Window::Width() / 2, Window::Height()*0.7);
	book_btns.push_back(new PushButton("�ɴ�Ѽ"));
	book_btns_thr.push_back(new PushButton("����"));
	elf.push_back(new Monster("����ѿ","��"));
	loadimage(&(elf[8]->img), "./Images/Bellsprout.png", Window::Width() / 2, Window::Height()*0.7);
	book_btns.push_back(new PushButton("����ѿ"));
	book_btns_thr.push_back(new PushButton("����"));
	elf.push_back(new Monster("�������", "ˮ"));
	loadimage(&(elf[9]->img), "./Images/Poliwag.png", Window::Width() / 2, Window::Height()*0.7);
	book_btns.push_back(new PushButton("�������"));
	book_btns_thr.push_back(new PushButton("����"));
	elf.push_back(new Monster("������", "ˮ"));
	loadimage(&(elf[10]->img), "./Images/Slowpoke.png", Window::Width() / 2, Window::Height()*0.7);
	book_btns.push_back(new PushButton("������"));
	book_btns_thr.push_back(new PushButton("����"));
	elf.push_back(new Monster("��˹", "����"));
	loadimage(&(elf[11]->img), "./Images/Gastly.png", Window::Width() / 2, Window::Height()*0.7);
	book_btns.push_back(new PushButton("��˹"));
	book_btns_thr.push_back(new PushButton("����"));
	elf.push_back(new Monster("��������", "����"));
	loadimage(&(elf[12]->img), "./Images/Cubone.png", Window::Width() / 2, Window::Height()*0.7);
	book_btns.push_back(new PushButton("��������"));
	book_btns_thr.push_back(new PushButton("����"));
	elf.push_back(new Monster("�Դ���", "��"));
	loadimage(&(elf[13]->img), "./Images/Jynx.png", Window::Width() / 2, Window::Height()*0.7);
	book_btns.push_back(new PushButton("�Դ���"));
	book_btns_thr.push_back(new PushButton("����"));
	elf.push_back(new Monster("������", "ˮ"));
	loadimage(&(elf[14]->img), "./Images/Magikarp.png", Window::Width() / 2, Window::Height()*0.7);
	book_btns.push_back(new PushButton("������"));
	book_btns_thr.push_back(new PushButton("����"));
	elf.push_back(new Monster("�ղ�Ҷ", "��"));
	loadimage(&(elf[15]->img), "./Images/Chikorita.png", Window::Width() / 2, Window::Height()*0.7);
	book_btns.push_back(new PushButton("�ղ�Ҷ"));
	book_btns_thr.push_back(new PushButton("����"));
	elf.push_back(new Monster("���˱�", "����"));
	loadimage(&(elf[16]->img), "./Images/Togepi.png", Window::Width() / 2, Window::Height()*0.7);
	book_btns.push_back(new PushButton("���˱�"));
	book_btns_thr.push_back(new PushButton("����"));
	elf.push_back(new Monster("��β��", "һ��"));
	loadimage(&(elf[17]->img), "./Images/Skitty.png", Window::Width() / 2, Window::Height()*0.7);
	book_btns.push_back(new PushButton("��β��"));
	book_btns_thr.push_back(new PushButton("����"));


	int r = 0;
	for (int i = 0; i < book_btns.size(); i++)
	{
		book_btns[i]->setFixedSize(Window::Width() / 6, (Window::Height()-40) / 3);
		int bx = Window::Width() / 2;
		if (i == 3 || i == 4 || i == 5 || i == 12 || i == 13 || i == 14)
		{
			bx += book_btns[i]->width();
		}
		if (i == 6 || i == 7 || i == 8 || i == 15 || i == 16 || i == 17)
		{
			bx += (book_btns[i]->width()) * 2;
		}
		if (i == 3 || i == 6 || i == 9 || i == 12 || i == 15)
			r = 0;
		int by = r * book_btns[i]->height();
		r++;
		book_btns[i]->move(bx, by);
	}

	book_btns_sec.push_back(new PushButton("�鿴����̬"));
	evolved.push_back(new Evolve("����", "��"));  //���ؿڴ����ֽ���̬
	loadimage(&(evolved[0]->img), "./Images/Raichu.png", Window::Width() / 2, Window::Height()*0.8);
	book_btns_sec.push_back(new PushButton("�鿴����̬"));
	evolved.push_back(new Evolve("���ܲ�", "��"));
	loadimage(&(evolved[1]->img), "./Images/Ivysaur.png", Window::Width() / 2, Window::Height()*0.8);
	book_btns_sec.push_back(new PushButton("�鿴����̬"));
	evolved.push_back(new Evolve("�����", "��"));
	loadimage(&(evolved[2]->img), "./Images/Charmeleon.png", Window::Width() / 2, Window::Height()*0.8);
	book_btns_sec.push_back(new PushButton("�鿴����̬"));
	evolved.push_back(new Evolve("�����", "ˮ"));
	loadimage(&(evolved[3]->img), "./Images/Wartortle.png", Window::Width() / 2, Window::Height()*0.8);
	book_btns_sec.push_back(new PushButton("�鿴����̬"));
	evolved.push_back(new Evolve("Ƥ����", "����"));
	loadimage(&(evolved[4]->img), "./Images/Clefable.png", Window::Width() / 2, Window::Height()*0.8);
	book_btns_sec.push_back(new PushButton("�鿴����̬")); 
	evolved.push_back(new Evolve("��β", "��"));
	loadimage(&(evolved[5]->img), "./Images/Ninetales.png", Window::Width() / 2, Window::Height()*0.8);
	book_btns_sec.push_back(new PushButton("�鿴����̬"));
	evolved.push_back(new Evolve("�ֿɶ�"));
	loadimage(&(evolved[6]->img), "./Images/Wigglytuff.png", Window::Width() / 2, Window::Height()*0.8);
	book_btns_sec.push_back(new PushButton("�鿴����̬"));
	evolved.push_back(new Evolve("���Ѽ", "ˮ"));
	loadimage(&(evolved[7]->img), "./Images/Golduck.png", Window::Width() / 2, Window::Height()*0.8);
	book_btns_sec.push_back(new PushButton("�鿴����̬"));
	evolved.push_back(new Evolve("��ʳ��", "��"));
	loadimage(&(evolved[8]->img), "./Images/Victreebel.png", Window::Width() / 2, Window::Height()*0.8);
	book_btns_sec.push_back(new PushButton("�鿴����̬"));
	evolved.push_back(new Evolve("�����", "ˮ"));
	loadimage(&(evolved[9]->img), "./Images/Poliwhirl.png", Window::Width() / 2, Window::Height()*0.8);
	book_btns_sec.push_back(new PushButton("�鿴����̬"));
	evolved.push_back(new Evolve("������", "������"));
	loadimage(&(evolved[10]->img), "./Images/Slowbro.png", Window::Width() / 2, Window::Height()*0.8);
	book_btns_sec.push_back(new PushButton("�鿴����̬"));
	evolved.push_back(new Evolve("����", "����"));
	loadimage(&(evolved[11]->img), "./Images/Gengar.png", Window::Width() / 2, Window::Height()*0.8);
	book_btns_sec.push_back(new PushButton("�鿴����̬"));
	evolved.push_back(new Evolve("��������", "����"));
	loadimage(&(evolved[12]->img), "./Images/Marowak.png", Window::Width() / 2, Window::Height()*0.8);
	book_btns_sec.push_back(new PushButton("�鿴����̬"));
	evolved.push_back(new Evolve("�Դ���", "��"));
	loadimage(&(evolved[13]->img), "./Images/Jynx.png", Window::Width() / 2, Window::Height()*0.8);
	book_btns_sec.push_back(new PushButton("�鿴����̬"));
	evolved.push_back(new Evolve("������", "ˮ"));
	loadimage(&(evolved[14]->img), "./Images/Gyarados.png", Window::Width() / 2, Window::Height()*0.8);
	book_btns_sec.push_back(new PushButton("�鿴����̬"));
	evolved.push_back(new Evolve("���ÿ�", "��"));
	loadimage(&(evolved[15]->img), "./Images/Meganium.png", Window::Width() / 2, Window::Height()*0.8);
	book_btns_sec.push_back(new PushButton("�鿴����̬"));
	evolved.push_back(new Evolve("���˻���", "����"));
	loadimage(&(evolved[16]->img), "./Images/Togetic.png", Window::Width() / 2, Window::Height()*0.8);
	book_btns_sec.push_back(new PushButton("�鿴����̬"));
	evolved.push_back(new Evolve("����è", "һ��"));
	loadimage(&(evolved[17]->img), "./Images/Delcatty.png", Window::Width() / 2, Window::Height()*0.8);

	for (int i = 0; i < book_btns_sec.size(); i++)
	{
		book_btns_sec[i]->setFixedSize(200, 50);
		int bx = Window::Width() / 2 - book_btns_sec[i]->width() - 20;
		int by = Window::Height() - book_btns_sec[i]->height() - 20;
		book_btns_sec[i]->move(bx, by);
	}
	for (int i = 0; i < book_btns_thr.size(); i++)
	{
		book_btns_thr[i]->setFixedSize(200, 50);
		int bx = Window::Width() / 2 - book_btns_thr[i]->width() - 20;
		int by = Window::Height() - 2 * book_btns_thr[i]->height() - 20;
		book_btns_thr[i]->move(bx, by);
	}
}

void Operate::initBackPack()
{
	loadimage(&backPack_bk, "./Images/backPack_bk.JPEG", Window::Width(), Window::Height());
	m_boss = new PushButton("��������boss", Window::Width() / 2 - t_width * 8, Window::Height() / 2 + t_height,260,50);

	boss.push_back(new Boss("���ع�", "������", 0.4));
	loadimage(&(boss[0]->img), "./Images/Arbok.png", Window::Width() / 2, Window::Height()*0.8);
	boss_btns.push_back(new PushButton("??"));
	boss.push_back(new Boss("������", "����", 0.6));
	loadimage(&(boss[1]->img), "./Images/Golbat.png", Window::Width() / 2, Window::Height()*0.8);
	boss_btns.push_back(new PushButton("??"));
	boss.push_back(new Boss("����", "һ��", 0.3));
	loadimage(&(boss[2]->img), "./Images/Meowth.png", Window::Width() / 2, Window::Height()*0.8);
	boss_btns.push_back(new PushButton("??"));
	boss.push_back(new Boss("������", "��", 0.5));
	loadimage(&(boss[3]->img), "./Images/Rapidash.png", Window::Width() / 2, Window::Height()*0.8);
	boss_btns.push_back(new PushButton("??"));
	boss.push_back(new Boss("˫����˹", "����", 0.7));
	loadimage(&(boss[4]->img), "./Images/Weezing.png", Window::Width() / 2, Window::Height()*0.8);
	boss_btns.push_back(new PushButton("??"));
	boss.push_back(new Boss("������", "����", 0.5));
	loadimage(&(boss[5]->img), "./Images/Muk.png", Window::Width() / 2, Window::Height()*0.8);
	boss_btns.push_back(new PushButton("??"));
	boss.push_back(new Boss("Ҭ����", "��", 0.2));
	loadimage(&(boss[6]->img), "./Images/Exeggutor.png", Window::Width() / 2, Window::Height()*0.8);
	boss_btns.push_back(new PushButton("??"));
	boss.push_back(new Boss("������", "��", 0.4));
	loadimage(&(boss[7]->img), "./Images/Snorlax.png", Window::Width() / 2, Window::Height()*0.8);
	boss_btns.push_back(new PushButton("??"));
	boss.push_back(new Boss("����", "ˮ", 0.8));
	loadimage(&(boss[8]->img), "./Images/Quagsire.png", Window::Width() / 2, Window::Height()*0.8);
	boss_btns.push_back(new PushButton("??"));

	int r = 0;
	for (int i = 0; i < boss_btns.size(); i++)
	{
		boss_btns[i]->setFixedSize(Window::Width() / 6, Window::Height() / 3);
		int bx = Window::Width() / 2;
		if (i == 3 || i == 4 || i == 5 )
		{
			bx += boss_btns[i]->width();
		}
		if (i == 6 || i == 7 || i == 8 )
		{
			bx += (boss_btns[i]->width()) * 2;
		}
		if (i == 3 || i == 6 )
			r = 0;
		int by = r * boss_btns[i]->height();
		r++;
		boss_btns[i]->move(bx, by);
	}
}

void Operate::initMap()
{
	loadimage(&map_bk, "./Images/map_bk.jpeg", Window::Width(), Window::Height());
	m_catch = new PushButton("��׽", Window::Width() / 2 - 150, Window::Height() / 2 - 20, 300, 90);
}

void Operate::drawBackground()
{
	putimage(0, 0, &bk);
}

void Operate::ShowPlayerInfo()
{
	putimage(0, 0, &backPack_bk);
	setfillcolor(WHITE);
	solidroundrect(Window::Width() / 2 - t_width * 10, Window::Height() / 2 - 4 * t_height, 
		Window::Width() / 2 + t_width * 10, Window::Height() / 2 + 4 * t_height, 20, 20);
	settextcolor(BLACK);
	settextstyle(t_height, t_width, "����");
	outtextxy(Window::Width() / 2 - t_width * 8, Window::Height() / 2 - 3 * t_height, "������");
	outtextxy(Window::Width() / 2 , Window::Height() / 2 - 3 * t_height, me.name.c_str());
	outtextxy(Window::Width() / 2 - t_width * 8, Window::Height() / 2 - 2 * t_height, "��ӵ�У�  ֻ");
	char s[5];
	sprintf(s, "%d", me.ba);//outtextxy����������Ϊ�ַ�������Ҫ�����������ʹ��sprintf
	outtextxy(Window::Width() / 2, Window::Height() / 2 - 2 * t_height, s);
	outtextxy(Window::Width() / 2 - t_width * 8, Window::Height() / 2 -  t_height, "�ȼ���");
	char s1[5];
	sprintf(s1, "%d", me.level);
	outtextxy(Window::Width() / 2, Window::Height() / 2 -  t_height, s1);
	info_boss();
}

void Operate::ShowMap()
{
	putimage(0, 0, &map_bk);
	srand(time(NULL));
	settextstyle(t_height*2, t_width*2, "����");
	map_catch();
	switch (catch_flag)
	{
	case 1:
		elf[ca]->condition = 'Y';
		outtextxy(Window::Width() / 2 - t_width * 20, Window::Height() / 2 - 100, "��׽�ɹ�����ӵ�У�");
		outtextxy(Window::Width() / 2 + t_width * 16, Window::Height() / 2 - 100, elf[ca]->name.c_str()); break;
	case 3:
		outtextxy(Window::Width() / 2 - t_width * 32, Window::Height() / 2 - 100, "��׽ʧ��:-(���ظ���׽");
		outtextxy(Window::Width() / 2 + t_width * 16, Window::Height() / 2 - 100, elf[ca]->name.c_str()); break;
	case 2:
		outtextxy(Window::Width() / 2 - t_width * 16, Window::Height() / 2 - 100, "��׽ʧ��:-(���ȼ�����"); break;
	default:break;
	}
	switch (boss_flag)
	{
	case 1:
		outtextxy(Window::Width() / 2 - t_width * 20, Window::Height() / 2 + 100, "����BOSS��");
		outtextxy(Window::Width() / 2 + t_width * 16, Window::Height() / 2 + 100, boss[boss_index]->name.c_str()); break;
	case 0:
		outtextxy(Window::Width() / 2 - t_width * 20, Window::Height() / 2 + 100, "δ����Boss"); break;
	}
}

void Operate::ShowElf()
{
	putimage(0, 0, &bookbk);
	settextstyle(t_height, t_width, "����");
	setbkmode(TRANSPARENT);
	//ȷ����ťλ��
	int id = book();
	book_sec();
	book_thr();
	drawPageTurnButton();
	if(flag==1)
	{
		putimage(0, 0, &evolved[temp]->img);
		settextcolor(WHITE);
		outtextxy(t_width, Window::Height() - 3 * t_height, evolved[temp]->name.c_str());//����ַ���ʱ��c_str()����ȡ������ĸ
		outtextxy(t_width, Window::Height() - 2 * t_height, "���ԣ�");
		outtextxy(t_width * 6, Window::Height() - 2 * t_height, evolved[temp]->feature.c_str());
		return;
	}
	putimage(0, 0, &elf[temp]->img);
	settextcolor(WHITE);
	outtextxy(t_width, Window::Height() - 4 * t_height, elf[temp]->name.c_str());
	outtextxy(t_width, Window::Height() - 3 * t_height, "���ԣ�");
	outtextxy(t_width * 6, Window::Height() - 3 * t_height, elf[temp]->feature.c_str());
	outtextxy(t_width, Window::Height() - 2 * t_height, "״̬��");
	if (elf[temp]->condition == 'Y')
		outtextxy(t_width * 6, Window::Height() - 2 * t_height, "ӵ��");
	else
		outtextxy(t_width * 6, Window::Height() - 2 * t_height, "Ұ��");
	outtextxy(t_width, Window::Height() - t_height, "�ȼ���");
	char s[5];
	sprintf(s, "%d", elf[temp]->level);//outtextxy����������Ϊ�ַ�������Ҫ�����������ʹ��sprintf
	outtextxy(t_width * 6, Window::Height() - t_height, s);
}

void Operate::ShowBoss()
{
	settextstyle(t_height, t_width, "����");
	putimage(0, 0, &bookbk);
	setbkmode(TRANSPARENT);
	for (int i = 0; i < boss.size(); i++)
	{
		if (boss[i]->condition == 'Y')
		{
			boss_btns[i]->changeText(boss[i]->name);
		}
		boss_btns[i]->show();
		boss_btns[i]->changeColor(m_msg);
		//����ť���
		if (boss_btns[i]->isClicked())
		{
			temp = i;
		}
	}
	if (boss[temp]->condition == 'Y')
	{
		putimage(0, 0, &boss[temp]->img);
		settextcolor(WHITE);
		outtextxy(t_width, Window::Height() - 4 * t_height, boss[temp]->name.c_str());
		outtextxy(t_width, Window::Height() - 3 * t_height, "���ԣ�");
		outtextxy(t_width * 6, Window::Height() - 3 * t_height, boss[temp]->feature.c_str());
		outtextxy(t_width, Window::Height() - 2 * t_height, "�������ʣ�");
		char s[5];
		sprintf(s, "%01.1f", boss[temp]->rate);
		outtextxy(t_width * 10, Window::Height() - 2 * t_height, s);
	}
}

bool Operate::Timer(int ms)
{
	static DWORD t;
	if (clock() - t > ms)
	{
		t = clock();
		return true;
	}
	return false;
}

void Operate::Search()
{
	string n;
	cout << "�����������ҵ����ƣ�";
	while (cin >> n)
	{
		for (int i = 0; i < elf.size(); i++)
		{
			if (elf[i]->name == n)
			{
				cout << "���ҵ���" << elf[i]->name << endl
					<< "״̬��";
				if (elf[i]->condition == 'Y')
					cout << "ӵ��" << endl;
				else
					cout << "Ұ��" << endl;
				cout << "�ȼ���" << elf[i]->level << endl << "���ԣ�" << elf[i]->feature << endl;
			}
		}
		cout<< "�����������ҵ����ƣ�";
	}
}
