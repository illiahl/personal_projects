rm(list = ls())
library(tidyverse)
library(shiny)
library(shinythemes)

# Setting up
options(repr.plot.res = 300)

working_directory_path = "/home/ilyahl/Documents/Projects/for_cv/personal_projects/statistics_and_data_analysis/interactive_dashboard"
setwd(working_directory_path)

new_names <- c(ethnicity = 'race/ethnicity', education_level = 'parental level of education', preparation_course = 'test preparation course', math_score = 'math score', reading_score = 'reading score', writing_score = 'writing score')

df <- as.tibble(read_csv("StudentsPerformance.csv")) %>%
    rename(all_of(new_names)) %>%
    mutate(across(c(gender, ethnicity, education_level, lunch, preparation_course), as.factor))

levels(df$education_level) <- c("associates_degree", "bachelors_degree", "high_school", "masters_degree", "some_college", "some_high_school")
levels(df$ethnicity) <- c("group_A", "group_B", "group_C", "group_D", "group_E")


# BUilding web application

ui <- fluidPage(theme=shinytheme("united"),
    navbarPage("Dashboard",

        tabPanel("Home",
            mainPanel(
                h1("Students Performance in Exams dataset"),
                paste("Dataset contains marks secured by the students in some subjects based on various factors."),

                h2("Basic data visualisation:"),
                plotOutput(outputId = "plot_home")
            )
        ),

        tabPanel("Distributions",
            sidebarPanel(
                h3("Input parameters"),

                selectInput(inputId="subject", 
                    label="Subject:", 
                    choices=c("Math" = "math", "Reading" = "reading", "Writing" = "writing")
                ),
                checkboxGroupInput(inputId="gender", 
                    label="Gender:", 
                    choices=c("Female" = "female", "Male" = "male")
                ),
                checkboxGroupInput(inputId="ethnicity", 
                    label="Ethnicity:", 
                    choices=c("Group A" = "group_A", "Group B" = "group_B", "Group C" = "group_C", "Group D" = "group_D", "Group E" = "group_E")
                ),
                checkboxGroupInput(inputId="education_level", 
                    label="Education level:", 
                    choices=c("Associates Degree" = "associates_degree", "Bachelors Degree" = "bachelors_degree", "High School" = "high_school", "Masters Degree" = "masters_degree", "Some College" = "some_college", "Some High School" = "some_high_school")
                ),
                checkboxGroupInput(inputId="lunch",
                    label="Lunch:",
                    choices=c("Free/Reduced" = "free/reduced", "Standard" = "standard")
                )
            ),

            mainPanel(
                h2("Distribution plot:"),
                plotOutput(outputId="plot_distribution"),

                h2("Normality test:"),
                verbatimTextOutput(outputId="text_distribution")
            )
        ),

        tabPanel("Comparisons",
            sidebarPanel(
                h3("Input parameters"),

                selectInput(inputId="subject_comparison", 
                    label="Subject:", 
                    choices=c("Math" = "math", "Reading" = "reading", "Writing" = "writing")
                ),

                selectInput(inputId="compare_on", 
                    label="Compare on:", 
                    choices=c("Gender" = "gender", "Ethnicity" = "ethnicity", "Education level" = "education_level", "Lunch" = "lunch")
                ),
            ),

            mainPanel(
                h2("Data plot:"),
                plotOutput(outputId="plot_comparison"),

                h2("Comparison results:"),
                verbatimTextOutput(outputId="text_comparison")
            )
        ),

        tabPanel("About",
            markdown("
            # A simple web application for such data analysis tasks as distribution visualisation and sample comparison.

            The data is taken from [Students Performance in Exams dataset](https://www.kaggle.com/datasets/spscientist/students-performance-in-exams/?select=StudentsPerformance.csv).

            The dataset consists of 1000 observations of marks secured by the students in various subjects based on some factors.

            #### Dataset variables: 
            - *gender*
            - *ethnicity*
            - *education level*
            - *lunch (represents wether the person had lunch before exams)*
            - *preparation course (represents wether the persons has completed test preparation course)*
            - *math score*
            - *reading score*
            - *writing score*

            #### Functional of dashboard:
            - *visualisation of distribution based on checked factors and normality test*
            - *comparison of two samples by given factor*

            **The inspiration of creation of this web application is to understand the influence of different factors on students performance**.
            ")
        )
    )
)

server <- function(input, output, session){

    output$plot_home <- renderPlot({
        df %>% 
            select(gender, math_score, reading_score, writing_score) %>% 
            pivot_longer(!gender, names_to = "type", values_to = "score") %>% 
            select(-gender) %>% 
            mutate(across(type, as.factor)) %>%
            ggplot(aes(x=type, y=score)) + 
            geom_boxplot(aes(fill=type), alpha=0.5, show.legend=FALSE) + 
            labs(x="", y="value", title="Performance among students") +
            theme(plot.title=element_text(size=24), axis.title.y=element_text(size=18), axis.title.x=element_text(size=18), axis.text.x=element_text(size=18)) +
            scale_color_brewer(palette="Set1")
    })

    output$plot_distribution <- renderPlot({

        if ((length(input$gender) == 0) || (length(input$ethnicity) == 0) || (length(input$education_level) == 0) || (length(input$lunch) == 0)) {
            df %>% 
                ggplot()
        } 
        
        else if (input$subject == "math") {
            mean <- (df %>% 
                        filter(gender %in% as.vector(input$gender), 
                            ethnicity %in% as.vector(input$ethnicity), 
                            education_level %in% as.vector(input$education_level),
                            lunch %in% as.vector(input$lunch)))$math_score %>% 
                            mean()
            
            sd <- (df %>% 
                        filter(gender %in% as.vector(input$gender), 
                            ethnicity %in% as.vector(input$ethnicity), 
                            education_level %in% as.vector(input$education_level),
                            lunch %in% as.vector(input$lunch)))$math_score %>% 
                            sd()

           df %>% 
                filter(gender %in% as.vector(input$gender), 
                    ethnicity %in% as.vector(input$ethnicity), 
                    education_level %in% as.vector(input$education_level),
                    lunch %in% as.vector(input$lunch)) %>%
                ggplot(aes(x=math_score)) + 
                geom_histogram(aes(y=after_stat(density)), alpha=0.4, color="#a39797", fill="#64b9ff29", linewidth=1) + 
                geom_density(color="#272121", linewidth=1.5) +
                geom_rug() +
                labs(x="", y="", caption=paste("mean = ", mean, "\nsd = ", sd)) +
                theme(axis.text.x=element_text(size=16), axis.text.y=element_text(size=16), plot.caption=element_text(size=14))
        } 
        
        else if (input$subject == "reading") {
            mean <- (df %>% 
                        filter(gender %in% as.vector(input$gender), 
                            ethnicity %in% as.vector(input$ethnicity), 
                            education_level %in% as.vector(input$education_level),
                            lunch %in% as.vector(input$lunch)))$writing_score %>% 
                            mean()
            
            sd <- (df %>% 
                        filter(gender %in% as.vector(input$gender), 
                            ethnicity %in% as.vector(input$ethnicity), 
                            education_level %in% as.vector(input$education_level),
                            lunch %in% as.vector(input$lunch)))$writing_score %>% 
                            sd()

           df %>% 
                filter(gender %in% as.vector(input$gender), 
                    ethnicity %in% as.vector(input$ethnicity), 
                    education_level %in% as.vector(input$education_level),
                    lunch %in% as.vector(input$lunch)) %>%
                ggplot(aes(x=reading_score)) + 
                geom_histogram(aes(y=after_stat(density)), alpha=0.4, color="#a39797", fill="#64b9ff29", linewidth=1) + 
                geom_density(color="#272121", linewidth=1.5) +
                geom_rug() +
                labs(x="", y="", caption=paste("mean = ", mean, "\nsd = ", sd)) +
                theme(axis.text.x=element_text(size=16), axis.text.y=element_text(size=16), plot.caption=element_text(size=14))
        } 
        
        else if (input$subject == "writing") {
            mean <- (df %>% 
                        filter(gender %in% as.vector(input$gender), 
                            ethnicity %in% as.vector(input$ethnicity), 
                            education_level %in% as.vector(input$education_level),
                            lunch %in% as.vector(input$lunch)))$writing_score %>% 
                            mean()
            
            sd <- (df %>% 
                        filter(gender %in% as.vector(input$gender), 
                            ethnicity %in% as.vector(input$ethnicity), 
                            education_level %in% as.vector(input$education_level),
                            lunch %in% as.vector(input$lunch)))$writing_score %>% 
                            sd()

           df %>% 
                filter(gender %in% as.vector(input$gender), 
                    ethnicity %in% as.vector(input$ethnicity), 
                    education_level %in% as.vector(input$education_level),
                    lunch %in% as.vector(input$lunch)) %>%
                ggplot(aes(x=writing_score)) + 
                geom_histogram(aes(y=after_stat(density)), alpha=0.4, color="#a39797", fill="#64b9ff29", linewidth=1) + 
                geom_density(color="#272121", linewidth=1.5) +
                geom_rug() +
                labs(x="", y="", caption=paste("mean = ", mean, "\nsd = ", sd)) +
                theme(axis.text.x=element_text(size=16), axis.text.y=element_text(size=16), plot.caption=element_text(size=14))
        }
    })

    output$text_distribution <- renderText({
        if ((length(input$gender) == 0) || (length(input$ethnicity) == 0) || (length(input$education_level) == 0) || (length(input$lunch) == 0)) {
            paste(" ")
        } 
        
        else if (input$subject == "math") {
            test <- (df %>% 
                filter(gender %in% as.vector(input$gender), 
                    ethnicity %in% as.vector(input$ethnicity), 
                    education_level %in% as.vector(input$education_level),
                    lunch %in% as.vector(input$lunch)))$math_score %>%
                    shapiro.test()
            
            if (test$p.value > 0.05) {
                paste("With confidence level of 95% the distribution has no significant difference from normal distribution based on Shapiro-Wilk test.\nThe distribution can be thout of as normal distribution.")
            }
            else {
               paste("With confidence level of 95% the distribution has significant difference from normal distribution based on Shapiro-Wilk test.\nThe distribution can not be thout of as normal distribution.")
            }
        } 
        
        else if (input$subject == "reading") {
            test <- (df %>% 
                filter(gender %in% as.vector(input$gender), 
                    ethnicity %in% as.vector(input$ethnicity), 
                    education_level %in% as.vector(input$education_level),
                    lunch %in% as.vector(input$lunch)))$reading_score %>%
                    shapiro.test()

            if (test$p.value > 0.05) {
                paste("With confidence level of 95% the distribution has no significant difference from normal distribution based on Shapiro-Wilk test.\nThe distribution can be thout of as normal distribution.")
            }
            else {
               paste("With confidence level of 95% the distribution has significant difference from normal distribution based on Shapiro-Wilk test.\nThe distribution can not be thout of as normal distribution.")
            }
        } 
        
        else if (input$subject == "writing") {
            test <- (df %>% 
                filter(gender %in% as.vector(input$gender), 
                    ethnicity %in% as.vector(input$ethnicity), 
                    education_level %in% as.vector(input$education_level),
                    lunch %in% as.vector(input$lunch)))$writing_score %>%
                    shapiro.test()
            
            if (test$p.value > 0.05) {
                paste("With confidence level of 95% the distribution has no significant difference from normal distribution based on Shapiro-Wilk test.\nThe distribution can be thout of as normal distribution.")
            }
            else {
               paste("With confidence level of 95% the distribution has significant difference from normal distribution based on Shapiro-Wilk test.\nThe distribution can not be thout of as normal distribution.")
            }
        }
    })

    output$plot_comparison <- renderPlot({
        if (input$subject_comparison == "math")
        {
            if(input$compare_on == "gender")
            {
                df %>% 
                ggplot(aes(x="", y=math_score)) + 
                geom_violin(alpha = 0.1, fill="#80aaaa", linewidth=0.5, trim=FALSE) +
                geom_boxplot(alpha=0.4, fill="#80aaaa", linewidth=1.25) + 
                labs(x="", y="") + 
                theme(axis.text.y=element_text(size=16), strip.text=element_text(size=20)) + 
                facet_wrap(vars(gender))
            }

            else if (input$compare_on == "ethnicity")
            {
                df %>% 
                ggplot(aes(x="", y=math_score)) + 
                geom_violin(alpha = 0.1, fill="#80aaaa", linewidth=0.5, trim=FALSE) +
                geom_boxplot(alpha=0.4, fill="#80aaaa", linewidth=1.25) + 
                labs(x="", y="") + 
                theme(axis.text.y=element_text(size=16), strip.text=element_text(size=20)) + 
                facet_wrap(vars(ethnicity))
            }

            else if (input$compare_on == "education_level")
            {
                df %>% 
                ggplot(aes(x="", y=math_score)) + 
                geom_violin(alpha = 0.1, fill="#80aaaa", linewidth=0.5, trim=FALSE) +
                geom_boxplot(alpha=0.4, fill="#80aaaa", linewidth=1.25) + 
                labs(x="", y="") + 
                theme(axis.text.y=element_text(size=16), strip.text=element_text(size=20)) + 
                facet_wrap(vars(education_level))
            }

            else if (input$compare_on == "lunch") 
            {
               df %>% 
                ggplot(aes(x="", y=math_score)) + 
                geom_violin(alpha = 0.1, fill="#80aaaa", linewidth=0.5, trim=FALSE) +
                geom_boxplot(alpha=0.4, fill="#80aaaa", linewidth=1.25) + 
                labs(x="", y="") + 
                theme(axis.text.y=element_text(size=16), strip.text=element_text(size=20)) + 
                facet_wrap(vars(lunch))
            }
        }

        else if (input$subject_comparison == "reading")
        {
            if(input$compare_on == "gender")
            {
                df %>% 
                ggplot(aes(x="", y=reading_score)) + 
                geom_violin(alpha = 0.1, fill="#80aaaa", linewidth=0.5, trim=FALSE) +
                geom_boxplot(alpha=0.4, fill="#80aaaa", linewidth=1.25) + 
                labs(x="", y="") + 
                theme(axis.text.y=element_text(size=16), strip.text=element_text(size=20)) + 
                facet_wrap(vars(gender))
            }

            else if (input$compare_on == "ethnicity")
            {
                df %>% 
                ggplot(aes(x="", y=reading_score)) + 
                geom_violin(alpha = 0.1, fill="#80aaaa", linewidth=0.5, trim=FALSE) +
                geom_boxplot(alpha=0.4, fill="#80aaaa", linewidth=1.25) + 
                labs(x="", y="") + 
                theme(axis.text.y=element_text(size=16), strip.text=element_text(size=20)) + 
                facet_wrap(vars(ethnicity))
            }

            else if (input$compare_on == "education_level")
            {
                df %>% 
                ggplot(aes(x="", y=reading_score)) + 
                geom_violin(alpha = 0.1, fill="#80aaaa", linewidth=0.5, trim=FALSE) +
                geom_boxplot(alpha=0.4, fill="#80aaaa", linewidth=1.25) + 
                labs(x="", y="") + 
                theme(axis.text.y=element_text(size=16), strip.text=element_text(size=20)) + 
                facet_wrap(vars(education_level))
            }

            else if (input$compare_on == "lunch") 
            {
               df %>% 
                ggplot(aes(x="", y=reading_score)) + 
                geom_violin(alpha = 0.1, fill="#80aaaa", linewidth=0.5, trim=FALSE) +
                geom_boxplot(alpha=0.4, fill="#80aaaa", linewidth=1.25) + 
                labs(x="", y="") + 
                theme(axis.text.y=element_text(size=16), strip.text=element_text(size=20)) + 
                facet_wrap(vars(lunch))
            }
        }

        else if (input$subject_comparison == "writing") 
        {
            if(input$compare_on == "gender")
            {
                df %>% 
                ggplot(aes(x="", y=writing_score)) + 
                geom_violin(alpha = 0.1, fill="#80aaaa", linewidth=0.5, trim=FALSE) +
                geom_boxplot(alpha=0.4, fill="#80aaaa", linewidth=1.25) + 
                labs(x="", y="") + 
                theme(axis.text.y=element_text(size=16), strip.text=element_text(size=20)) + 
                facet_wrap(vars(gender))
            }

            else if (input$compare_on == "ethnicity")
            {
                df %>% 
                ggplot(aes(x="", y=writing_score)) + 
                geom_violin(alpha = 0.1, fill="#80aaaa", linewidth=0.5, trim=FALSE) +
                geom_boxplot(alpha=0.4, fill="#80aaaa", linewidth=1.25) + 
                labs(x="", y="") + 
                theme(axis.text.y=element_text(size=16), strip.text=element_text(size=20)) + 
                facet_wrap(vars(ethnicity))
            }

            else if (input$compare_on == "education_level")
            {
                df %>% 
                ggplot(aes(x="", y=writing_score)) + 
                geom_violin(alpha = 0.1, fill="#80aaaa", linewidth=0.5, trim=FALSE) +
                geom_boxplot(alpha=0.4, fill="#80aaaa", linewidth=1.25) + 
                labs(x="", y="") + 
                theme(axis.text.y=element_text(size=16), strip.text=element_text(size=20)) + 
                facet_wrap(vars(education_level))
            }

            else if (input$compare_on == "lunch") 
            {
               df %>% 
                ggplot(aes(x="", y=writing_score)) + 
                geom_violin(alpha = 0.1, fill="#80aaaa", linewidth=0.5, trim=FALSE) +
                geom_boxplot(alpha=0.4, fill="#80aaaa", linewidth=1.25) + 
                labs(x="", y="") + 
                theme(axis.text.y=element_text(size=16), strip.text=element_text(size=20)) + 
                facet_wrap(vars(lunch))
            }
        }
    })

    output$text_comparison <- renderText({
        if (input$subject_comparison == "math")
        {
            if(input$compare_on == "gender")
            {
                x1 <- (df %>% filter(gender == "female"))$math_score
                x2 <- (df %>% filter(gender == "male"))$math_score
                test <- wilcox.test(x1, x2)

                if (test$p.value > 0.05) {
                    paste("With confidence level of 95% in average samples has no significant differences from each other based on Wilcoxon test.")
                }
                else {
                    paste("With confidence level of 95% in average samples has significant differences from each other based on Wilcoxon test.")
                }
            }
            else if (input$compare_on == "ethnicity")
            {
                x1 <- (df %>% filter(ethnicity == "group_A"))$math_score
                x2 <- (df %>% filter(ethnicity == "group_B"))$math_score
                x3 <- (df %>% filter(ethnicity == "group_C"))$math_score
                x4 <- (df %>% filter(ethnicity == "group_D"))$math_score
                x5 <- (df %>% filter(ethnicity == "group_E"))$math_score
                test <- kruskal.test(list(x1, x2, x3, x4, x5))

                if (test$p.value > 0.05) {
                    paste("With confidence level of 95% in average samples has no significant differences from each other based on Kruskal-Wallis test.")
                }
                else {
                    paste("With confidence level of 95% in average samples has significant differences from each other based on Kruskal-Wallis test.")
                }
            }

            else if (input$compare_on == "education_level")
            {
                x1 <- (df %>% filter(education_level == "associates_degree"))$math_score
                x2 <- (df %>% filter(education_level == "bachelors_degree"))$math_score
                x3 <- (df %>% filter(education_level == "high_school"))$math_score
                x4 <- (df %>% filter(education_level == "masters_degree"))$math_score
                x5 <- (df %>% filter(education_level == "some_college"))$math_score
                x6 <- (df %>% filter(education_level == "some_high_school"))$math_score
                test <- kruskal.test(list(x1, x2, x3, x4, x5, x6))

                if (test$p.value > 0.05) {
                    paste("With confidence level of 95% in average samples has no significant differences from each other based on Kruskal-Wallis test.")
                }
                else {
                    paste("With confidence level of 95% in average samples has significant differences from each other based on Kruskal-Wallis test.")
                }
            }

            else if (input$compare_on == "lunch") 
            {
                x1 <- (df %>% filter(lunch == "free/reduced"))$math_score
                x2 <- (df %>% filter(lunch == "standard"))$math_score
                test <- wilcox.test(x1, x2)

                if (test$p.value > 0.05) {
                    paste("With confidence level of 95% in average samples has no significant differences from each other based on Wilcoxon test.")
                }
                else {
                    paste("With confidence level of 95% in average samples has significant differences from each other based on Wilcoxon test.")
                }
            }
        }

        else if (input$subject_comparison == "reading")
        {
            if(input$compare_on == "gender")
            {
                x1 <- (df %>% filter(gender == "female"))$reading_score
                x2 <- (df %>% filter(gender == "male"))$reading_score
                test <- wilcox.test(x1, x2)

                if (test$p.value > 0.05) {
                    paste("With confidence level of 95% in average samples has no significant differences from each other based on Wilcoxon test.")
                }
                else {
                    paste("With confidence level of 95% in average samples has significant differences from each other based on Wilcoxon test.")
                }
            }
            else if (input$compare_on == "ethnicity")
            {
                x1 <- (df %>% filter(ethnicity == "group_A"))$reading_score
                x2 <- (df %>% filter(ethnicity == "group_B"))$reading_score
                x3 <- (df %>% filter(ethnicity == "group_C"))$reading_score
                x4 <- (df %>% filter(ethnicity == "group_D"))$reading_score
                x5 <- (df %>% filter(ethnicity == "group_E"))$reading_score
                test <- kruskal.test(list(x1, x2, x3, x4, x5))

                if (test$p.value > 0.05) {
                    paste("With confidence level of 95% in average samples has no significant differences from each other based on Kruskal-Wallis test.")
                }
                else {
                    paste("With confidence level of 95% in average samples has significant differences from each other based on Kruskal-Wallis test.")
                }
            }

            else if (input$compare_on == "education_level")
            {
                x1 <- (df %>% filter(education_level == "associates_degree"))$reading_score
                x2 <- (df %>% filter(education_level == "bachelors_degree"))$reading_score
                x3 <- (df %>% filter(education_level == "high_school"))$reading_score
                x4 <- (df %>% filter(education_level == "masters_degree"))$reading_score
                x5 <- (df %>% filter(education_level == "some_college"))$reading_score
                x6 <- (df %>% filter(education_level == "some_high_school"))$reading_score
                test <- kruskal.test(list(x1, x2, x3, x4, x5, x6))

                if (test$p.value > 0.05) {
                    paste("With confidence level of 95% in average samples has no significant differences from each other based on Kruskal-Wallis test.")
                }
                else {
                    paste("With confidence level of 95% in average samples has significant differences from each other based on Kruskal-Wallis test.")
                }
            }

            else if (input$compare_on == "lunch") 
            {
                x1 <- (df %>% filter(lunch == "free/reduced"))$reading_score
                x2 <- (df %>% filter(lunch == "standard"))$reading_score
                test <- wilcox.test(x1, x2)

                if (test$p.value > 0.05) {
                    paste("With confidence level of 95% in average samples has no significant differences from each other based on Wilcoxon test.")
                }
                else {
                    paste("With confidence level of 95% in average samples has significant differences from each other based on Wilcoxon test.")
                }
            }
        }

        else if (input$subject_comparison == "writing") 
        {
            if(input$compare_on == "gender")
            {
                x1 <- (df %>% filter(gender == "female"))$writing_score
                x2 <- (df %>% filter(gender == "male"))$writing_score
                test <- wilcox.test(x1, x2)

                if (test$p.value > 0.05) {
                    paste("With confidence level of 95% in average samples has no significant differences from each other based on Wilcoxon test.")
                }
                else {
                    paste("With confidence level of 95% in average samples has significant differences from each other based on Wilcoxon test.")
                }
            }
            else if (input$compare_on == "ethnicity")
            {
                x1 <- (df %>% filter(ethnicity == "group_A"))$writing_score
                x2 <- (df %>% filter(ethnicity == "group_B"))$writing_score
                x3 <- (df %>% filter(ethnicity == "group_C"))$writing_score
                x4 <- (df %>% filter(ethnicity == "group_D"))$writing_score
                x5 <- (df %>% filter(ethnicity == "group_E"))$writing_score
                test <- kruskal.test(list(x1, x2, x3, x4, x5))

                if (test$p.value > 0.05) {
                    paste("With confidence level of 95% in average samples has no significant differences from each other based on Kruskal-Wallis test.")
                }
                else {
                    paste("With confidence level of 95% in average samples has significant differences from each other based on Kruskal-Wallis test.")
                }
            }

            else if (input$compare_on == "education_level")
            {
                x1 <- (df %>% filter(education_level == "associates_degree"))$writing_score
                x2 <- (df %>% filter(education_level == "bachelors_degree"))$writing_score
                x3 <- (df %>% filter(education_level == "high_school"))$writing_score
                x4 <- (df %>% filter(education_level == "masters_degree"))$writing_score
                x5 <- (df %>% filter(education_level == "some_college"))$writing_score
                x6 <- (df %>% filter(education_level == "some_high_school"))$writing_score
                test <- kruskal.test(list(x1, x2, x3, x4, x5, x6))

                if (test$p.value > 0.05) {
                    paste("With confidence level of 95% in average samples has no significant differences from each other based on Kruskal-Wallis test.")
                }
                else {
                    paste("With confidence level of 95% in average samples has significant differences from each other based on Kruskal-Wallis test.")
                }
            }

            else if (input$compare_on == "lunch") 
            {
                x1 <- (df %>% filter(lunch == "free/reduced"))$writing_score
                x2 <- (df %>% filter(lunch == "standard"))$writing_score
                test <- wilcox.test(x1, x2)

                if (test$p.value > 0.05) {
                    paste("With confidence level of 95% in average samples has no significant differences from each other based on Wilcoxon test.")
                }
                else {
                    paste("With confidence level of 95% in average samples has significant differences from each other based on Wilcoxon test.")
                }
            }
        }
    })
}

shinyApp(ui=ui, server=server)