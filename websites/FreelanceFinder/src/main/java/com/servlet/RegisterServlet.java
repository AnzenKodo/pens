package com.servlet;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.DB.DBConnect;
import com.dao.JobDao;
import com.dao.UserDao;
import com.entity.Jobs;
import com.entity.User;

@WebServlet("/register")
public class RegisterServlet extends HttpServlet{

	@Override
	protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
		try {
			String name = req.getParameter("name");
			String email = req.getParameter("email");
			String password = req.getParameter("password");
			String qualification = req.getParameter("qualification");
			String role = "user";

			User user= new User();
			user.setName(name);
			user.setEmail(email);
			user.setPassword(password);
			user.setQualification(qualification);
			user.setRole(role);

			HttpSession session = req.getSession();

			//saving jobs to db
			UserDao userDao = new UserDao(DBConnect.getConnection());
			boolean add = userDao.addUser(user);
			if(add) {
				System.out.println("user added");
				session.setAttribute("userobj", user);
				session.setAttribute("succMsg", "user registered successfuly");
				resp.sendRedirect("index.jsp");
			} else {
				System.out.println("job not added");
				session.setAttribute("succMsg", "user not added. error coming..");
				resp.sendRedirect("register.jsp");
			}

		} catch (Exception e) {
			e.printStackTrace();
		}
	}

}
