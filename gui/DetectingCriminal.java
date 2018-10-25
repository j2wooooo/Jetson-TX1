import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

import java.awt.Image;
import java.awt.event.KeyListener;
import java.awt.Dimension;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Container;
import java.awt.Font;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.GraphicsEnvironment;
import java.awt.GraphicsDevice;
import java.io.IOException;

public class DetectingCriminal extends JFrame implements ActionListener{

	private static String user_identification; // user_identification = 1,  if hwayoung
												//                     = 2,  if hayoung
	private static String detection_date_time;
	private static String detection_accuracy;
	private static Dimension dimen;
	
	public DetectingCriminal() {
		
		// background image
		ImageIcon back_icon = new ImageIcon("back.png");
		Image background_img = back_icon.getImage().getScaledInstance(742,599,java.awt.Image.SCALE_SMOOTH); // resize image
		setContentPane(new JLabel(new ImageIcon(background_img)));
		
		/* full screen - in window
		this.setExtendedState( getExtendedState() | this.MAXIMIZED_BOTH);
		this.setUndecorated(true); // full screen
		setSize((int)dimen.width,(int)dimen.height); // size
		*/
		
		// full screen - in ubuntu
		GraphicsEnvironment env = GraphicsEnvironment.getLocalGraphicsEnvironment();
		GraphicsDevice device = env.getDefaultScreenDevice();
		device.setFullScreenWindow(this);
		
		
		setLayout(null);
		
		//load image
		ImageIcon criminal_img;
		ImageIcon usr_img;
		
		if(user_identification.equals(new String("1"))) {                // user - hwayoung
			criminal_img = new ImageIcon("crimial_hwa.jpg");
			usr_img = new ImageIcon("/home/nvidia/darkent/pictures/"+detection_date_time+".jpg");
		
			
		}else {                                      // user - hayoung
			criminal_img = new ImageIcon("img.png");
			usr_img = new ImageIcon("img.png");
		}
		
		// resize criminal image
		Image new_criminal_img = criminal_img.getImage().getScaledInstance(320,240,java.awt.Image.SCALE_SMOOTH); // resize image
		criminal_img = new ImageIcon(new_criminal_img);
		
		JLabel criminal_ImgBox = new JLabel(criminal_img);
		criminal_ImgBox.setBounds(15,120,criminal_img.getIconWidth(),criminal_img.getIconHeight());
		
		// resize user image
		Image new_user_img = usr_img.getImage().getScaledInstance(320,240,java.awt.Image.SCALE_SMOOTH); // resize image
		usr_img = new ImageIcon(new_user_img);
		
		JLabel usr_ImgBox = new JLabel(usr_img);
		usr_ImgBox.setBounds(380,120,usr_img.getIconWidth(),usr_img.getIconHeight());
		
		// * ATM User Information*
		// location
		JLabel label_atm_use_location = new JLabel("119, Academy-ro, Yeonsu-gu ");
		label_atm_use_location.setBounds(465,393,300,100);
		label_atm_use_location.setFont(new Font("Serif",Font.BOLD,14));
		// time
		JLabel label_atm_use_time = new JLabel(detection_date_time);
		label_atm_use_time.setBounds(435,418,300,100);
		label_atm_use_time.setFont(new Font("Serif",Font.BOLD,15));
		
		
		//JLabel label_accuracy = new JLabel("Index of Similarity : "+detection_accuracy +"% \n");	
		JLabel label_accuracy = new JLabel(" 0% \n");
		label_accuracy.setBounds(460, 500,500,80);
		label_accuracy.setFont(new Font("Serif",Font.BOLD,30));
		label_accuracy.setForeground(Color.RED);
		
		this.add(label_atm_use_location);
		this.add(label_atm_use_time);
		this.add(label_accuracy);
		this.add(criminal_ImgBox);
		this.add(usr_ImgBox);
		
		this.addKeyListener(new MyKeyListener());
		
		setVisible(true);
		
		//refresh frame
		int accuracy = Integer.parseInt(detection_accuracy);
		for(int i=0; i<=accuracy; i++) {
			label_accuracy.setText(i +"% \n");
			SwingUtilities.updateComponentTreeUI(this);
			try {
				Thread.sleep(30);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		
	}
	
	class MyKeyListener extends KeyAdapter{
		public void keyPressed(KeyEvent e) {
			
			if(e.getKeyCode()==27) { // end
				System.exit(0);
			}
		}
	}
	
	
	public static void main(String[] args) {
		// 범죄자 누구인지(화영,하영) 이미지 캡쳐사진 이름, 검출 정확도
		// 예시 : hwayoung 2018-10-24xxx 92
		
		// TODO Auto-generated method stub
		System.out.println("자바 테스트");
		
		// get args value
		//user_identification = "1"; // args[0]
		//detection_date_time = "2018-10-24_XXXX";// args[1]
		//detection_accuracy = "94"; // args[2]
		
		user_identification = args[0]; // args[0] = 1 : hwayoung 
		detection_date_time = args[1];// args[1] = "2018-10-24_XXX"
		detection_accuracy = args[2]; // args[2] = "94"
		
		dimen = Toolkit.getDefaultToolkit().getScreenSize();
		
		DetectingCriminal av=new DetectingCriminal();
		
	}


	@Override
	public void actionPerformed(ActionEvent arg0) {
		// TODO Auto-generated method stub
		
	}
}


