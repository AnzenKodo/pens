<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ page isELIgnored="false" %>

<nav class="navbar navbar-expand-lg navbar-dark bg-custom">
  <a class="navbar-brand" href="#">FreelanceFinder</a>
  <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarSupportedContent" aria-controls="navbarSupportedContent" aria-expanded="false" aria-label="Toggle navigation">
    <span class="navbar-toggler-icon"></span>
  </button>


  <div class="collapse navbar-collapse" id="navbarSupportedContent">
    <ul class="navbar-nav mr-auto">
      <li class="nav-item active">
        <a class="nav-link" href="index.jsp">Home <span class="sr-only">(current)</span></a>
      </li>

      <c:if test="${userobj.role eq 'admin'}">
      		<li class="nav-item"><a class="nav-link" href="add_job.jsp"><i class="fas fa-plus-circle"></i> Post Job</a></li>
      		<li class="nav-item"><a class="nav-link" href="view_jobs.jsp"><i class="fas fa-eye"></i> View Job</a></li>
      </c:if>

      <c:if test="${userobj.role eq 'user'}">
      		<li class="nav-item"><a class="nav-link" href="all_jobs.jsp"><i class="fas fa-eye"></i> View Jobs</a></li>
      </c:if>

    </ul>
    <form class="form-inline my-2 my-lg-0" action="/searchjob" method="post">

    	<c:if test="${not empty userobj }">

    		<c:if test="${userobj.role eq 'admin' }">
    			<a href="admin.jsp" class="btn btn-light mr-1"><i class="fas fa-user"></i> Admin</a>
    		</c:if>
    		<c:if test="${userobj.role eq 'user' }">
    			<a href="admin.jsp" class="btn btn-light mr-1"><i class="fas fa-user"></i> ${userobj.name}</a>
    		</c:if>

			<a href="logout" class="btn btn-light"><i class="fas fa-sign-in-alt"></i> Logout</a>
		</c:if>
		<c:if test="${empty userobj }">
			<a href="login.jsp" class="btn btn-light mr-1"><i class="fas fa-sign-in-alt"></i> Login</a>
			<a href="register.jsp" class="btn btn-light"><i class="fas fa-user .mr-sm-2"></i> Signup</a>
		</c:if>

      <input class="form-control mr-sm-2 ml-sm-1" type="search" placeholder="Search" aria-label="Search">
      <button class="btn btn-outline-success my-2 my-sm-0" type="submit">Search</button>
    </form>
  </div>
</nav>
<div class="container" style="padding: 2rem 0">
	<c:if test="${not empty succMsg}">

		<h4 class="alert alert-primary" role="alert">${succMsg}</h4>
		<c:remove var="succMsg" />
	</c:if>
