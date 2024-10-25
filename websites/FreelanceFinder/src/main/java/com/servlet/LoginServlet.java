package com.servlet;

import java.io.IOException;
import java.sql.PreparedStatement;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.DB.DBConnect;
import com.dao.UserDao;
import com.entity.User;

@WebServlet("/login")
public class LoginServlet extends HttpServlet{

	@Override
	protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {

		try {
			String email = req.getParameter("email");
			String password = req.getParameter("password");

			HttpSession session = req.getSession();

			if("admin@gmail.com".equals(email) && "password".equals(password)) {
				System.out.println(email);
				User user = new User();
				user.setRole("admin");
				session.setAttribute("userobj", user);
				resp.sendRedirect("admin.jsp");
			} else {
				UserDao dao = new UserDao(DBConnect.getConnection());
				User user = dao.validateUser(email, password);
				if(user !=null) {
					session.setAttribute("userobj", user);
					resp.sendRedirect("index.jsp");
				} else {
					session.setAttribute("succMsg", "user credentials not correct...");
					resp.sendRedirect("login.jsp");
				}

			}

		} catch (Exception e) {
			e.printStackTrace();
		}
	}



}
