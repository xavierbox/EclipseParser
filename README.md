# EclipseParser
Small library to parse X files in c++. It has only 3 methods, all static. Doesnt depend on any third parties.
The lib allows to read simulation results from visage, eclipse, and intersect into c++ vectors. See example code:

EclipseReaderCpp.cpp


<pre style="font-family:Consolas;font-size:16px;color:black;background:white;"><span style="color:blue;">int</span>&nbsp;main()
{
	{
<span style="color:green;">//get&nbsp;a&nbsp;list&nbsp;of&nbsp;keywords&nbsp;(similar&nbsp;to&nbsp;Pete&#39;s&nbsp;c#&nbsp;code)&nbsp;</span>
		<span style="color:#2b91af;">string</span>&nbsp;file&nbsp;=&nbsp;<span style="color:#a31515;">&quot;D:\\GPMTESTS\\PALEOV3_0.X0000&quot;</span>;
		<span style="color:#2b91af;">map</span>&lt;<span style="color:#2b91af;">string</span>,&nbsp;<span style="color:#2b91af;">KeywordDescription</span>&gt;&nbsp;keywords&nbsp;=&nbsp;<span style="color:#2b91af;">EclipseReader</span>::GetKeywords(file);
 
<span style="color:green;">//print&nbsp;the&nbsp;found&nbsp;keys&nbsp;</span>
		std::for_each(keywords.begin(),&nbsp;keywords.end(),&nbsp;[&amp;](std::<span style="color:#2b91af;">pair</span>&lt;<span style="color:#2b91af;">string</span>,&nbsp;<span style="color:#2b91af;">KeywordDescription</span>&gt;&nbsp;<span style="color:gray;">value</span>)&nbsp;
			{std::cout&nbsp;<span style="color:teal;">&lt;&lt;</span>&nbsp;<span style="color:gray;">value</span>.second<span style="color:teal;">&lt;&lt;</span>&nbsp;std::endl;&nbsp;});
 
<span style="color:green;">//load&nbsp;one&nbsp;array&nbsp;</span>
		std::<span style="color:#2b91af;">string</span>&nbsp;key&nbsp;=&nbsp;<span style="color:#a31515;">&quot;TOTSTRXY&quot;</span>;
		<span style="color:#2b91af;">vector</span>&lt;<span style="color:blue;">float</span>&gt;&nbsp;values;
		<span style="color:blue;">bool</span>&nbsp;success&nbsp;=&nbsp;<span style="color:#2b91af;">EclipseReader</span>::LoadEclipseDataArray&lt;<span style="color:blue;">float</span>&gt;(key,&nbsp;file,&nbsp;values);
 
<span style="color:green;">//print&nbsp;the&nbsp;array&nbsp;</span>
		<span style="color:blue;">if</span>&nbsp;(success)
		{
			std::for_each(values.begin(),&nbsp;values.end(),&nbsp;[&amp;](<span style="color:blue;">float</span>&nbsp;<span style="color:gray;">value</span>)&nbsp;{std::cout&nbsp;<span style="color:teal;">&lt;&lt;</span>&nbsp;<span style="color:gray;">value</span>&nbsp;<span style="color:teal;">&lt;&lt;</span>&nbsp;std::endl;&nbsp;});
		}
 
<span style="color:green;">//load&nbsp;and&nbsp;print&nbsp;another&nbsp;array&nbsp;(type&nbsp;guessed&nbsp;by&nbsp;the&nbsp;vector&nbsp;type)</span>
		<span style="color:blue;">if</span>(&nbsp;<span style="color:#2b91af;">EclipseReader</span>::LoadEclipseDataArray(<span style="color:#a31515;">&quot;ROCKDISY&quot;</span>,&nbsp;file,&nbsp;values))
		{
			std::for_each(values.begin(),&nbsp;values.end(),&nbsp;[&amp;](<span style="color:blue;">float</span>&nbsp;<span style="color:gray;">value</span>)&nbsp;{std::cout&nbsp;<span style="color:teal;">&lt;&lt;</span>&nbsp;<span style="color:gray;">value</span>&nbsp;<span style="color:teal;">&lt;&lt;</span>&nbsp;std::endl;&nbsp;});
		}
 
<span style="color:green;">//try&nbsp;to&nbsp;load&nbsp;and&nbsp;print&nbsp;an&nbsp;array&nbsp;that&nbsp;doesnt&nbsp;exist&nbsp;&nbsp;</span>
		<span style="color:blue;">if</span>&nbsp;(<span style="color:#2b91af;">EclipseReader</span>::LoadEclipseDataArray(<span style="color:#a31515;">&quot;$$$$$$$$&quot;</span>,&nbsp;file,&nbsp;values))
		{
			std::for_each(values.begin(),&nbsp;values.end(),&nbsp;[&amp;](<span style="color:blue;">float</span>&nbsp;<span style="color:gray;">value</span>)&nbsp;{std::cout&nbsp;<span style="color:teal;">&lt;&lt;</span>&nbsp;<span style="color:gray;">value</span>&nbsp;<span style="color:teal;">&lt;&lt;</span>&nbsp;std::endl;&nbsp;});
		}
		<span style="color:blue;">else</span>&nbsp;
		{
			cout&nbsp;<span style="color:teal;">&lt;&lt;</span>&nbsp;<span style="color:#a31515;">&quot;This&nbsp;array&nbsp;doesnt&nbsp;exist.&nbsp;False&nbsp;was&nbsp;returned.&nbsp;No&nbsp;exceptions&nbsp;propagate&quot;</span>&nbsp;<span style="color:teal;">&lt;&lt;</span>&nbsp;std::endl;
		}
	}</pre>
	
	
